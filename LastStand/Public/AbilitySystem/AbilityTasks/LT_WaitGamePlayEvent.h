// Omar Sweiti

#pragma once

#include "CoreMinimal.h"
#include "Abilities/Async/AbilityAsync_WaitGameplayEvent.h"
#include "LT_WaitGamePlayEvent.generated.h"

/**
 * 
 */
UCLASS()
class LASTSTAND_API ULT_WaitGamePlayEvent : public UAbilityAsync_WaitGameplayEvent
{
	GENERATED_BODY()
public:

	UFUNCTION(BlueprintCallable, Category = "Ability|Async", meta = (DefaultToSelf = "TargetActor", BlueprintInternalUseOnly = "TRUE"))
	static ULT_WaitGamePlayEvent* WaitGameplayEventToActorProxy(AActor* TargetActor, UPARAM(meta=(GameplayTagFilter="GameplayEventTagsCategory")) FGameplayTag EventTag, bool OnlyTriggerOnce = false, bool OnlyMatchExact = true);

	
	void StartActivation();
};
