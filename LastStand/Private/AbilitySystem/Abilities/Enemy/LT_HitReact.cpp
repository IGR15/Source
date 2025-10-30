// Omar Sweiti


#include "AbilitySystem/Abilities/Enemy/LT_HitReact.h"

void ULT_HitReact::CashHitDirectionVectors(AActor* Instigator)
{
	AvatarForward=GetAvatarActorFromActorInfo()->GetActorForwardVector();
	const FVector AvatarLocation= GetAvatarActorFromActorInfo()->GetActorLocation();
	const FVector InstigatorLocation=Instigator->GetActorLocation();

	ToInstigator=InstigatorLocation-AvatarLocation;
	ToInstigator.Normalize();
}
