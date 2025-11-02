// Omar Sweiti

#pragma once

#include "CoreMinimal.h"
#include "AttributeSet.h"
#include "AbilitySystem/LT_AttributeSet.h"
#include "Kismet/BlueprintAsyncActionBase.h"
#include "LT_AttributeChangeTask.generated.h"


class UAbilitySystemComponent;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FOnAttributeChanged,FGameplayAttribute,Attribute,float ,NewValue,float,Oldvalue);
/**
 * 
 */
UCLASS(BlueprintType,meta=(ExposedAsyncProxy=AsyncTask))
class LASTSTAND_API ULT_AttributeChangeTask : public UBlueprintAsyncActionBase
{
	GENERATED_BODY()
public:

	UPROPERTY(BlueprintAssignable)
	FOnAttributeChanged OnAttributeChanged;

	UFUNCTION(BlueprintCallable,meta=(BlueprintInternalUseOnly="true"))
	static ULT_AttributeChangeTask* ListenForAttributeChange(UAbilitySystemComponent* AbilitySystemComponent,FGameplayAttribute Attribute);

	UFUNCTION(BlueprintCallable)
	void EndTask();

	TWeakObjectPtr<UAbilitySystemComponent>ASC;

	FGameplayAttribute AttributeToListenFor;

	void AttributeChanged(const FOnAttributeChangeData& Data);
};
