// Omar Sweiti


#include "AbilitySystem/Abilities/Enemy/LT_SearchForTarget.h"

#include "AIController.h"
#include "Abilities/Async/AbilityAsync_WaitGameplayEvent.h"

#include "AbilitySystem/AbilityTasks/LT_WaitGamePlayEvent.h"
#include "Abilities/Tasks/AbilityTask_WaitDelay.h"
#include "Characters/LT_EnemyCharacter.h"
#include "LTGamePlayTags/LTTags.h"
#include "Tasks/AITask_MoveTo.h"
#include "Utils/LT_BluePrintLibrary.h"

ULT_SearchForTarget::ULT_SearchForTarget()
{
	InstancingPolicy=EGameplayAbilityInstancingPolicy::InstancedPerActor;
	NetExecutionPolicy=EGameplayAbilityNetExecutionPolicy::ServerOnly;
}

void ULT_SearchForTarget::ActivateAbility(const FGameplayAbilitySpecHandle Handle,
	const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo,
	const FGameplayEventData* TriggerEventData)
{
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);

	OwningEnemy=Cast<ALT_EnemyCharacter>(GetAvatarActorFromActorInfo());
	check(OwningEnemy.IsValid());

	OwningAIController=Cast<AAIController>(OwningEnemy->GetController());
	check(OwningAIController.IsValid());

	StartSearch();
	
	WaitGameplayEventTask=ULT_WaitGamePlayEvent::WaitGameplayEventToActorProxy(GetAvatarActorFromActorInfo(),LTTags::Events::Enemy::EndAttack);

	WaitGameplayEventTask->EventReceived.AddDynamic(this,&ThisClass::EndAttackEventReceived);
	WaitGameplayEventTask->StartActivation();
	
	
}
void ULT_SearchForTarget::StartSearch()
{
	if (bDrawDebugs)GEngine->AddOnScreenDebugMessage(-1,3.f,FColor::Red,FString::Printf(TEXT("Searching for Target")));
	if (!OwningEnemy.IsValid())return;
	
	const float SearchDelay=FMath::RandRange(OwningEnemy->MinAttackDelay,OwningEnemy->MaxAttackDelay);
	SearchDelayTask=UAbilityTask_WaitDelay::WaitDelay(this,SearchDelay);
	SearchDelayTask->OnFinish.AddDynamic(this,&ThisClass::Search);
	SearchDelayTask->Activate();
}
inline void ULT_SearchForTarget::EndAttackEventReceived(FGameplayEventData Payload)
{
	if (OwningEnemy.IsValid()&&!OwningEnemy->bIsBeingLaunched)
	{
		StartSearch();
	}
}

void ULT_SearchForTarget::Search()
{
	const FVector SearchOrigen=GetAvatarActorFromActorInfo()->GetActorLocation();
	if (!OwningEnemy.IsValid())return;
	FClosestActorWithTagResult ClosestActorWithResult= ULT_BluePrintLibrary::FindClosestActorWithTag(GetAvatarActorFromActorInfo(),SearchOrigen,LaststandTags::Player,OwningEnemy->SearchRange);

	TargetBaseCharacter=Cast<ALT_BaseCharacter>(ClosestActorWithResult.Actor);
	if(!TargetBaseCharacter.IsValid())
	{
		StartSearch();
		return;
	}
	if (TargetBaseCharacter->IsAlive())
	{
		MoveToTargetAndAttack();
	}
	else
	{
		StartSearch();
	}
}

void ULT_SearchForTarget::MoveToTargetAndAttack()
{
	if (!OwningEnemy.IsValid()||!OwningAIController.IsValid()||!TargetBaseCharacter.IsValid())return;
	if (!OwningEnemy->IsAlive())
	{
		StartSearch();
		return;
	}
	MoveToLocationOrActorTask=UAITask_MoveTo::AIMoveTo(
		OwningAIController.Get(),
		FVector(),
		TargetBaseCharacter.Get(),
		OwningEnemy->AcceptenceRaidus
		);

	MoveToLocationOrActorTask->OnMoveTaskFinished.AddUObject(this,&ThisClass::AttackTarget);
	MoveToLocationOrActorTask->ConditionalPerformMove();
}

void ULT_SearchForTarget::AttackTarget(TEnumAsByte<EPathFollowingResult::Type> Result, AAIController* AIController)
{
	if (Result!= EPathFollowingResult::Success)
	{
		StartSearch();
		return;
	}
	OwningEnemy->RotateToTarget(TargetBaseCharacter.Get());
	
	AttackDelayTask=UAbilityTask_WaitDelay::WaitDelay(this,OwningEnemy->GetTimeLineLength());
	AttackDelayTask->OnFinish.AddDynamic(this,&ThisClass::Attack);
	AttackDelayTask->Activate();
}

void ULT_SearchForTarget::Attack()
{
	const FGameplayTag AttackTag=LTTags::LTAbilities::Enemy::Attack;
	GetAbilitySystemComponentFromActorInfo()->TryActivateAbilitiesByTag(AttackTag.GetSingleTagContainer());
}


