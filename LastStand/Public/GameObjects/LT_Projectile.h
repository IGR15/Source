// Omar Sweiti

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "LT_Projectile.generated.h"

UCLASS()
class LASTSTAND_API ALT_Projectile : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ALT_Projectile();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
};
