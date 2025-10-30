// Fill out your copyright notice in the Description page of Project Settings.


#include "LastStand/Public/Player/LT_PlayerState.h"
#include "LastStand/Public/AbilitySystem/LT_AbilitySystemComponent.h"
#include "LastStand/Public/AbilitySystem/LT_AttributeSet.h"

ALT_PlayerState::ALT_PlayerState()
{
	SetNetUpdateFrequency(100.f);

	AbilitySystemComponent=CreateDefaultSubobject<ULT_AbilitySystemComponent>("AbilitySystemComponent");

	AbilitySystemComponent->SetIsReplicated(true);
	AbilitySystemComponent->SetReplicationMode(EGameplayEffectReplicationMode::Mixed);

	AttributeSet=CreateDefaultSubobject<ULT_AttributeSet>("AttributeSet");
}

UAbilitySystemComponent* ALT_PlayerState::GetAbilitySystemComponent() const
{
	return AbilitySystemComponent;
}
