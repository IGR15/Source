// Omar Sweiti


#include "AbilitySystem/Abilities/LT_GamePlayAbility.h"

#include "Characters/LT_PlayerCharacter.h"

void ULT_GamePlayAbility::ActivateAbility(const FGameplayAbilitySpecHandle Handle,
                                          const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo,
                                          const FGameplayEventData* TriggerEventData)
{
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);

	
}


