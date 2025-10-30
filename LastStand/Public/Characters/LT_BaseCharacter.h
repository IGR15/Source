// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "AbilitySystemInterface.h"
#include "LT_BaseCharacter.generated.h"


class UAttributeSet;
class UGameplayEffect;
class UGameplayAbility;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FASCInitialized,UAbilitySystemComponent* ,ASC,UAttributeSet*,AS);

UCLASS(Abstract)
class LASTSTAND_API ALT_BaseCharacter : public ACharacter,public IAbilitySystemInterface
{
	GENERATED_BODY()

public:
	
	ALT_BaseCharacter();

	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;
	virtual UAttributeSet* GetAttributeSet()const{return nullptr;}

	UPROPERTY(BlueprintAssignable)
	FASCInitialized OnASCInitialized;
protected:
	void GiveStartUpAbilities();
	void InitializeAttributes();
private:
	UPROPERTY(EditDefaultsOnly,Category="GT|Abilities")
	TArray<TSubclassOf<UGameplayAbility>>StartUpAbilities;

	UPROPERTY(EditDefaultsOnly,Category="GT|Effects")
	TSubclassOf<UGameplayEffect>InitializeAttributeEffect;


};
