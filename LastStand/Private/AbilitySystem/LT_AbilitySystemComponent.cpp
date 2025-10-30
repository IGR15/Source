// Fill out your copyright notice in the Description page of Project Settings.


#include "LastStand/Public/AbilitySystem/LT_AbilitySystemComponent.h"
#include "LTGamePlayTags/LTTags.h"


// Sets default values for this component's properties
ULT_AbilitySystemComponent::ULT_AbilitySystemComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

	// ...
}

void ULT_AbilitySystemComponent::OnGiveAbility(FGameplayAbilitySpec& AbilitySpec)
{
	Super::OnGiveAbility(AbilitySpec);

	if (!IsValid(AbilitySpec.Ability))return;
	HandleAutoActivateAbilities(AbilitySpec);
}

void ULT_AbilitySystemComponent::OnRep_ActivateAbilities()
{
	Super::OnRep_ActivateAbilities();

	FScopedAbilityListLock ActiveScopeLock(*this);
	for (const FGameplayAbilitySpec& AbilitySpec:GetActivatableAbilities())
	{
		HandleAutoActivateAbilities(AbilitySpec);
	}
}

void ULT_AbilitySystemComponent::SetAbilityLevel(TSubclassOf<UGameplayAbility> AbilityClass, int32 Level)
{
	if (IsValid(GetAvatarActor())&&!GetAvatarActor()->HasAuthority())return;

	
	if (FGameplayAbilitySpec* AbilitySpec=FindAbilitySpecFromClass(AbilityClass))
	{
		AbilitySpec->Level=Level;
		MarkAbilitySpecDirty(*AbilitySpec);
	}
}

void ULT_AbilitySystemComponent::AddToAbilityLevel(TSubclassOf<UGameplayAbility> AbilityClass, int32 Level)
{
	if (IsValid(GetAvatarActor())&&!GetAvatarActor()->HasAuthority())return;

	
	if (FGameplayAbilitySpec* AbilitySpec=FindAbilitySpecFromClass(AbilityClass))
	{
		AbilitySpec->Level+=Level;
		MarkAbilitySpecDirty(*AbilitySpec);
	}
}

void ULT_AbilitySystemComponent::HandleAutoActivateAbilities(const FGameplayAbilitySpec& AbilitySpec)
{
	for (const FGameplayTag& Tag: AbilitySpec.Ability->GetAssetTags())
	{
		if (Tag.MatchesTagExact(LTTags::LTAbilities::ActivateOnGiven))
		{
			TryActivateAbility(AbilitySpec.Handle);
			return;
		}
	}
}



