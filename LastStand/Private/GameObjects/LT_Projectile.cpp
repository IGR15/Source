// Omar Sweiti


#include "GameObjects/LT_Projectile.h"

#include "Characters/LT_PlayerCharacter.h"
#include "AbilitySystemComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"


ALT_Projectile::ALT_Projectile()
{
	PrimaryActorTick.bCanEverTick = false;
	ProjectileMovement=CreateDefaultSubobject<UProjectileMovementComponent>("ProjectileMovementComponent");

	bReplicates=true;
}

void ALT_Projectile::NotifyActorBeginOverlap(AActor* OtherActor)
{
	Super::NotifyActorBeginOverlap(OtherActor);

	ALT_PlayerCharacter* PlayerCharacter=Cast<ALT_PlayerCharacter>(OtherActor);
	if (!IsValid(PlayerCharacter)&& !PlayerCharacter->IsAlive())return;

	UAbilitySystemComponent* AbilitySystemComponent=PlayerCharacter->GetAbilitySystemComponent();
	if (!IsValid(AbilitySystemComponent)||!HasAuthority())return;

	FGameplayEffectContextHandle ContextHandle= AbilitySystemComponent->MakeEffectContext();
	FGameplayEffectSpecHandle SpecHandle=AbilitySystemComponent->MakeOutgoingSpec(DamageEffect,1.f,ContextHandle);
	
	AbilitySystemComponent->ApplyGameplayEffectSpecToSelf(*SpecHandle.Data.Get());
	SpawnImpactEffects();
	Destroy();
}


