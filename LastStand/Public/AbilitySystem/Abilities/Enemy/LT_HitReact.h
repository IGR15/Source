// Omar Sweiti

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystem/Abilities/LT_GamePlayAbility.h"
#include "LT_HitReact.generated.h"

/**
 * 
 */
UCLASS()
class LASTSTAND_API ULT_HitReact : public ULT_GamePlayAbility
{
	GENERATED_BODY()
public:

	UFUNCTION(BlueprintCallable, Category = "GT|Abilities")
	void CashHitDirectionVectors(AActor* Instigator);
	
	UPROPERTY(BlueprintReadOnly,Category="GT|Abilities")
	FVector AvatarForward;

	UPROPERTY(BlueprintReadOnly,Category="GT|Abilities")
	FVector ToInstigator;
};
