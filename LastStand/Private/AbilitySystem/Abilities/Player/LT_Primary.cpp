// Omar Sweiti


#include "AbilitySystem/Abilities/Player/LT_Primary.h"
#include "AbilitySystemBlueprintLibrary.h"
#include "Engine/OverlapResult.h"
#include "LTGamePlayTags/LTTags.h"
void ULT_Primary::SendHitReactEventToActors(const TArray<AActor*>& ActorsHit)
{
	for (AActor* HitActor  : ActorsHit)
	{
		FGameplayEventData Payload;
		Payload.Instigator=GetAvatarActorFromActorInfo();
		UAbilitySystemBlueprintLibrary::SendGameplayEventToActor(HitActor,LTTags::Events::Enemy::HitReact,Payload);
	}
}


