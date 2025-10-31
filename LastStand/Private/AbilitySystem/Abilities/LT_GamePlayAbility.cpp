// Omar Sweiti


#include "AbilitySystem/Abilities/LT_GamePlayAbility.h"

#include "Characters/LT_PlayerCharacter.h"


void ULT_GamePlayAbility::BindToCharacterComboDelegate()
{
	if (ALT_PlayerCharacter* PlayerCharacter=Cast<ALT_PlayerCharacter>(GetAvatarActorFromActorInfo()))
	{
		PlayerCharacter->OnComboReset.AddDynamic(this,&ULT_GamePlayAbility::OnComboResetTimerExpired);
	}
}
void ULT_GamePlayAbility::OnComboResetTimerExpired()
{
	ALT_PlayerCharacter* PlayerCharacter=Cast<ALT_PlayerCharacter>(GetAvatarActorFromActorInfo());
	PlayerCharacter->ComboIndex=0;
}

void ULT_GamePlayAbility::ActivateAbility(const FGameplayAbilitySpecHandle Handle,
                                          const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo,
                                          const FGameplayEventData* TriggerEventData)
{
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);

	if (bDrawDebugs && IsValid(GEngine))
	{
		GEngine->AddOnScreenDebugMessage(-1,3.f,FColor::Cyan,FString::Printf(TEXT("%s Activated"),*GetName()));
	}
}


