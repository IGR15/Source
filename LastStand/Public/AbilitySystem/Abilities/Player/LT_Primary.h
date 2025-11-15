// Omar Sweiti

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystem/Abilities/LT_GamePlayAbility.h"
#include "LT_Primary.generated.h"

/**
 * 
 */
UCLASS()
class LASTSTAND_API ULT_Primary : public ULT_GamePlayAbility
{
	GENERATED_BODY()
public:

	UFUNCTION(BlueprintCallable,Category="GT|Abilities")
	void SendHitReactEventToActors(const TArray<AActor*>& ActorsHit);


protected:	
	UPROPERTY(EditDefaultsOnly,BlueprintReadOnly,Category="GT|Abilities")
	float HitBoxRadius=100.f;

	UPROPERTY(EditDefaultsOnly,BlueprintReadOnly,Category="GT|Abilities")
	float HitBoxForwardOffset=200.f;

	UPROPERTY(EditDefaultsOnly,BlueprintReadOnly,Category="GT|Abilities")
	float HitBoxElevationOffset=20.f;
};
