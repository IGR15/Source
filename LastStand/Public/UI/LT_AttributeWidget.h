// Omar Sweiti

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "AbilitySystem/LT_AttributeSet.h"
#include "LT_AttributeWidget.generated.h"

/**
 * 
 */
UCLASS()
class LASTSTAND_API ULT_AttributeWidget : public UUserWidget
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere,BlueprintReadOnly,Category="Crash|Attribute")
	FGameplayAttribute Attribute;

	UPROPERTY(EditAnywhere,BlueprintReadOnly,Category="Crash|Attribute")
	FGameplayAttribute MaxAttribute;

	void OnAttributeChange(const TTuple<FGameplayAttribute,FGameplayAttribute>& Pair,ULT_AttributeSet* AttributeSet);

	bool MatchesAttribute(const TTuple<FGameplayAttribute,FGameplayAttribute>& Pair)const;

	UFUNCTION(BlueprintImplementableEvent,meta=(DisplayName="OnAttributeChange"))
	void BP_OnAttributeChange(float NewValue,float NewMaxValue);
};
