// Fill out your copyright notice in the Description page of Project Settings.


#include "LastStand/Public/Characters/LT_EnemyCharacter.h"

#include "AbilitySystemBlueprintLibrary.h"
#include "AIController.h"
#include "LastStand/Public/AbilitySystem/LT_AbilitySystemComponent.h"
#include "LastStand/Public/AbilitySystem/LT_AttributeSet.h"
#include "LTGamePlayTags/LTTags.h"


// Sets default values
ALT_EnemyCharacter::ALT_EnemyCharacter()
{
	PrimaryActorTick.bCanEverTick = false;
	AbilitySystemComponent=CreateDefaultSubobject<ULT_AbilitySystemComponent>("ability system component");
	AbilitySystemComponent->SetIsReplicated(true);
	AbilitySystemComponent->SetReplicationMode(EGameplayEffectReplicationMode::Minimal);

	AttributeSet=CreateDefaultSubobject<ULT_AttributeSet>("AttributeSet");
}

UAbilitySystemComponent* ALT_EnemyCharacter::GetAbilitySystemComponent() const
{
	return AbilitySystemComponent;
}

UAttributeSet* ALT_EnemyCharacter::GetAttributeSet() const
{
	return AttributeSet;
}

void ALT_EnemyCharacter::HandleDeath()
{
	Super::HandleDeath();

	AAIController* AiController =GetController<AAIController>();
	if (!IsValid(AiController))return;
	AiController->StopMovement();
}

void ALT_EnemyCharacter::StopMovementUntilLanded()
{
	Super::StopMovementUntilLanded();
	
	bIsBeingLaunched=true;
	
	AAIController* AiController =GetController<AAIController>();
	if (!IsValid(AiController))return;
	AiController->StopMovement();
	if (!LandedDelegate.IsAlreadyBound(this,&ThisClass::EnableMovementOnLanded))
	{
		LandedDelegate.AddDynamic(this,&ThisClass::EnableMovementOnLanded);
	}
}
void ALT_EnemyCharacter::EnableMovementOnLanded(const FHitResult& Hit)
{
	bIsBeingLaunched=false;
	UAbilitySystemBlueprintLibrary::SendGameplayEventToActor(this,LTTags::Events::Enemy::EndAttack,FGameplayEventData());
	LandedDelegate.RemoveAll(this);
}

// Called when the game starts or when spawned
void ALT_EnemyCharacter::BeginPlay()
{
	Super::BeginPlay();
	if(!IsValid(GetAbilitySystemComponent()))return;

	GetAbilitySystemComponent()->InitAbilityActorInfo(this,this);
	OnASCInitialized.Broadcast(GetAbilitySystemComponent(),GetAttributeSet());

	if (!HasAuthority())return;

	GiveStartUpAbilities();
	InitializeAttributes();

	ULT_AttributeSet* LT_AttributeSet=Cast<ULT_AttributeSet>(GetAttributeSet());
	if (!IsValid(LT_AttributeSet))return;
	GetAbilitySystemComponent()->GetGameplayAttributeValueChangeDelegate(LT_AttributeSet->GetHealthAttribute()).AddUObject(this,&ThisClass::OnHealthChanged);
	
}



