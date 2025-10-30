// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AttributeSet.h"
#include "AbilitySystemComponent.h"
#include "LT_AttributeSet.generated.h"

/**
 * 
 */
#define ATTRIBUTE_ACCESSORS_BASIC(ClassName,PropertyName) \
	GAMEPLAYATTRIBUTE_PROPERTY_GETTER(ClassName, PropertyName) \
	GAMEPLAYATTRIBUTE_VALUE_GETTER(PropertyName) \
	GAMEPLAYATTRIBUTE_VALUE_SETTER(PropertyName) \
	GAMEPLAYATTRIBUTE_VALUE_INITTER(PropertyName)

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FAttributeInitialized);
UCLASS()
class LASTSTAND_API ULT_AttributeSet : public UAttributeSet
{
	GENERATED_BODY()
public:
	virtual void GetLifetimeReplicatedProps(TArray<class FLifetimeProperty>& OutLifetimeProps) const override;

	virtual void PostGameplayEffectExecute(const struct FGameplayEffectModCallbackData& Data) override;

	UPROPERTY(BlueprintAssignable)
	FAttributeInitialized  OnAttributeInitializedDelegate;
	
	UPROPERTY(ReplicatedUsing=OnRep_AttributesInitialized)
	bool bAttributeInitialized=false;

	UFUNCTION()
	void OnRep_AttributesInitialized();
	
	UPROPERTY(BlueprintReadOnly,ReplicatedUsing=onRep_Health)
	FGameplayAttributeData Health;

	UPROPERTY(BlueprintReadOnly,ReplicatedUsing=OnRep_MaxHealth)
	FGameplayAttributeData MaxHealth;
	
	UPROPERTY(BlueprintReadOnly,ReplicatedUsing=OnRep_Mana)
	FGameplayAttributeData Mana;
	
	UPROPERTY(BlueprintReadOnly,ReplicatedUsing=OnRep_MaxMana)
	FGameplayAttributeData MaxMana;
	
	UFUNCTION()
	void OnRep_Health(const FGameplayAttributeData& OldValue );

	UFUNCTION()
	void OnRep_MaxHealth(const FGameplayAttributeData& OldValue );
	
	UFUNCTION()
	void OnRep_Mana(const FGameplayAttributeData& OldValue );
	
	UFUNCTION()
	void OnRep_MaxMana(const FGameplayAttributeData& OldValue );
	
	ATTRIBUTE_ACCESSORS_BASIC(ThisClass,Health);
	ATTRIBUTE_ACCESSORS_BASIC(ThisClass,MaxHealth);
	ATTRIBUTE_ACCESSORS_BASIC(ThisClass,Mana);
	ATTRIBUTE_ACCESSORS_BASIC(ThisClass,MaxMana);
};
