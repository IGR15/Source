// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"
#include "AbilitySystemInterface.h"
#include "LT_PlayerState.generated.h"

/**
 * 
 */
class UAttributeSet;
class UAbilitySystemComponent;
UCLASS()
class LASTSTAND_API ALT_PlayerState : public APlayerState,public IAbilitySystemInterface
{
	GENERATED_BODY()
public:
	ALT_PlayerState();

	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;

	UAttributeSet* GetAttributeSet()const{return AttributeSet;}
private:
	UPROPERTY(VisibleAnywhere,Category="GT|Abilities")
	TObjectPtr<UAbilitySystemComponent>AbilitySystemComponent;

	UPROPERTY()
	TObjectPtr<UAttributeSet> AttributeSet;
};
