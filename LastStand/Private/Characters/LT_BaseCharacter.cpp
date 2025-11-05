// Fill out your copyright notice in the Description page of Project Settings.


#include "LastStand/Public/Characters/LT_BaseCharacter.h"
#include "AbilitySystemComponent.h"
#include "Net/UnrealNetwork.h"


namespace  LaststandTags
{
	const FName Player=FName("Player");
}
// Sets default values
ALT_BaseCharacter::ALT_BaseCharacter()
{
	PrimaryActorTick.bCanEverTick = false;
	//tick and refresh bone transforms whether rendered or not - for bond update on a dedicated server 
	GetMesh()->VisibilityBasedAnimTickOption=EVisibilityBasedAnimTickOption::AlwaysTickPoseAndRefreshBones;
}

void ALT_BaseCharacter::GetLifetimeReplicatedProps(TArray<class FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	DOREPLIFETIME(ThisClass,bAlive);
}

UAbilitySystemComponent* ALT_BaseCharacter::GetAbilitySystemComponent() const
{
	return nullptr;
}

void ALT_BaseCharacter::ResetAttributes()
{
	checkf(IsValid(ResetAttributesEffect),TEXT("InitializeAttributeEffect Not Set."));

	if (HasAuthority())
	{
		FGameplayEffectContextHandle Handle= GetAbilitySystemComponent()->MakeEffectContext();
		FGameplayEffectSpecHandle SpecHandle= GetAbilitySystemComponent()->MakeOutgoingSpec(ResetAttributesEffect,1.f,Handle);
		GetAbilitySystemComponent()->ApplyGameplayEffectSpecToSelf(*SpecHandle.Data.Get());
	}
}

void ALT_BaseCharacter::GiveStartUpAbilities()
{
	if (!IsValid(GetAbilitySystemComponent()))return;
	for (const auto& Ability:StartUpAbilities)
	{
		//FGamePlayAbilitySpec Are A light Wight Version of A GamePlayAbility
		FGameplayAbilitySpec AbilitySpec=FGameplayAbilitySpec(Ability);
		GetAbilitySystemComponent()->GiveAbility(AbilitySpec);
	}
}

void ALT_BaseCharacter::InitializeAttributes()
{
	checkf(IsValid(InitializeAttributeEffect),TEXT("InitializeAttributeEffect Not Set."));

	FGameplayEffectContextHandle Handle= GetAbilitySystemComponent()->MakeEffectContext();
	FGameplayEffectSpecHandle SpecHandle= GetAbilitySystemComponent()->MakeOutgoingSpec(InitializeAttributeEffect,1.f,Handle);
	GetAbilitySystemComponent()->ApplyGameplayEffectSpecToSelf(*SpecHandle.Data.Get());
}

void ALT_BaseCharacter::OnHealthChanged(const FOnAttributeChangeData& AttributeChangeData)
{
	if (AttributeChangeData.NewValue<=0.f)
	{
		HandleDeath();
	}
}
void ALT_BaseCharacter::HandleRespawn()
{
	bAlive=true;
}
void ALT_BaseCharacter::HandleDeath()
{
	
	bAlive=false;
	if (IsValid(GEngine))
	{
		GEngine->AddOnScreenDebugMessage(
			-1,
			3.f,
			FColor::Red,
			FString::Printf(TEXT("%s Has Died"),*GetName()));
	}
}

