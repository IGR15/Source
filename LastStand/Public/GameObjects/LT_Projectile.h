// Omar Sweiti

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "LT_Projectile.generated.h"

class UGameplayEffect;
class UProjectileMovementComponent;

UCLASS()
class LASTSTAND_API ALT_Projectile : public AActor
{
	GENERATED_BODY()

public:
	ALT_Projectile();
	virtual void NotifyActorBeginOverlap(AActor* OtherActor) override;

	UPROPERTY(EditAnywhere,BlueprintReadOnly,Category="GT|Damage",meta=(ExposeOnSpawn,ClampMin="0.0"))
	float Damage{-10.f};
	UFUNCTION(BlueprintImplementableEvent,Category="GT|Projectile")
	void SpawnImpactEffects();
	
private:

	UPROPERTY(VisibleAnywhere,Category="GT|Projectile")
	TObjectPtr<UProjectileMovementComponent> ProjectileMovement;

	UPROPERTY(EditDefaultsOnly,Category="GT|Effects")
	TSubclassOf<UGameplayEffect>DamageEffect;
};