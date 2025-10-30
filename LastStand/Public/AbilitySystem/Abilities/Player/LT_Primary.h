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
	TArray<AActor*> HitBoxOverlapTest();

	UFUNCTION(BlueprintCallable,Category="GT|Abilities")
	void SendHitReactEventToActors(const TArray<AActor*>& ActorsHit);
	
	

private:

	void DrawHitBoxOverlapDebugs(const TArray<FOverlapResult>& OverlapResults,const FVector& HitBoxLocation)const ;
	UPROPERTY(EditDefaultsOnly,Category="GT|Abilities")
	float HitBoxRadius=100.f;

	UPROPERTY(EditDefaultsOnly,Category="GT|Abilities")
	float HitBoxForwardOffset=200.f;

	UPROPERTY(EditDefaultsOnly,Category="GT|Abilities")
	float HitBoxElevationOffset=20.f;
};
