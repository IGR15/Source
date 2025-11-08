// Omar Sweiti

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystem/Abilities/LT_GamePlayAbility.h"
#include "LT_SearchForTarget.generated.h"

namespace EPathFollowingResult
{
	enum Type : int;
}

class ALT_BaseCharacter;
class AAIController;
class ALT_EnemyCharacter;
class ULT_WaitGamePlayEvent;
class UAbilityTask_WaitDelay;
class UAITask_MoveTo;
/**
 * 
 */
UCLASS()
class LASTSTAND_API ULT_SearchForTarget : public ULT_GamePlayAbility
{
	GENERATED_BODY()
public:
	ULT_SearchForTarget();

	virtual void ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData) override;

	TWeakObjectPtr<ALT_EnemyCharacter> OwningEnemy;
	TWeakObjectPtr<AAIController> OwningAIController;
	TWeakObjectPtr<ALT_BaseCharacter> TargetBaseCharacter;

private:

	UPROPERTY()
	TObjectPtr<UAITask_MoveTo> MoveToLocationOrActorTask;
	
	UPROPERTY()
	TObjectPtr<ULT_WaitGamePlayEvent>WaitGameplayEventTask;

	UPROPERTY()
	TObjectPtr<UAbilityTask_WaitDelay>SearchDelayTask;

	UPROPERTY()
	TObjectPtr<UAbilityTask_WaitDelay>AttackDelayTask;
	
	void StartSearch();

	UFUNCTION()
	void EndAttackEventReceived(FGameplayEventData Payload);

	UFUNCTION()
	void Search();

	void MoveToTargetAndAttack();

	UFUNCTION()
	void AttackTarget( TEnumAsByte<EPathFollowingResult::Type> Result, AAIController* AIController);

	UFUNCTION()
	void Attack();
};


