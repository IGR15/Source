// Omar Sweiti


#include "GameObjects/LT_Projectile.h"


// Sets default values
ALT_Projectile::ALT_Projectile()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void ALT_Projectile::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ALT_Projectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

