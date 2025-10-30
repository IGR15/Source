// Omar Sweiti

#pragma once

#include "CoreMinimal.h"
#include "Components/WidgetComponent.h"
#include "AbilitySystem/LT_AttributeSet.h"
#include "AttributeSet.h"
#include "LT_WidgetComponent.generated.h"

class ULT_AttributeSet;
class ULT_AbilitySystemComponent;
class ALT_BaseCharacter;
class UAbilitySystemComponent;
class UAttributeSet;

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class LASTSTAND_API ULT_WidgetComponent : public UWidgetComponent
{
	GENERATED_BODY()

public:
	

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere)
	TMap<FGameplayAttribute,FGameplayAttribute> AttributeMap;

private:
	TWeakObjectPtr<ALT_BaseCharacter> BaseCharacter;
	TWeakObjectPtr<ULT_AbilitySystemComponent>AbilitySystemComponent;
	TWeakObjectPtr<ULT_AttributeSet> AttributeSet;

	void InitAbilitySystemData();
	bool IsASCInitialized()const;
	void InitializeAttributesDelegate();
	void BindWidgetToAttributeChanges(UWidget* WidgetObject,const TTuple<FGameplayAttribute,FGameplayAttribute>& Pair)const;

	UFUNCTION()
	void OnASCInitialized(UAbilitySystemComponent* ASC,UAttributeSet* AS);

	UFUNCTION()
	void BindToAttributeChanges();
};
