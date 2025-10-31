// Omar Sweiti

#pragma once

#include "CoreMinimal.h"
#include "Abilities/GameplayAbility.h"
#include "LT_GamePlayAbility.generated.h"

/**
 * 
 */
UCLASS()
class LASTSTAND_API ULT_GamePlayAbility : public UGameplayAbility
{
	GENERATED_BODY()
	
	
	void BindToCharacterComboDelegate();
public:
	
	//virtual void ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData) override;
	void ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData) override;
	UPROPERTY(EditDefaultsOnly,BlueprintReadOnly,Category="LT|Debug")
	bool bDrawDebugs=false;
	UFUNCTION()
	void OnComboResetTimerExpired();

	
	
};
