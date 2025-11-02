// Fill out your copyright notice in the Description page of Project Settings.


#include "LastStand/Public/Characters/LT_EnemyCharacter.h"

#include "LastStand/Public/AbilitySystem/LT_AbilitySystemComponent.h"
#include "LastStand/Public/AbilitySystem/LT_AttributeSet.h"


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


