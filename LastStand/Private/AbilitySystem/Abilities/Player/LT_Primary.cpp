// Omar Sweiti


#include "AbilitySystem/Abilities/Player/LT_Primary.h"
#include "AbilitySystemBlueprintLibrary.h"
#include "Engine/OverlapResult.h"
#include "LTGamePlayTags/LTTags.h"

TArray<AActor*> ULT_Primary::HitBoxOverlapTest()
{
	TArray<AActor*> ActorsToIgnore;
	ActorsToIgnore.Add(GetAvatarActorFromActorInfo());

	// Ensure that the overlap test ignores the avatar actor 
	FCollisionQueryParams QueryParams;
	QueryParams.AddIgnoredActors(ActorsToIgnore);

	FCollisionResponseParams ResponseParams;
	ResponseParams.CollisionResponse.SetAllChannels(ECR_Ignore);
	ResponseParams.CollisionResponse.SetResponse(ECC_Pawn,ECR_Block);

	TArray<FOverlapResult> OverlapResults;
	FCollisionShape Sphere=FCollisionShape::MakeSphere(HitBoxRadius);

	const FVector ForwardVector=GetAvatarActorFromActorInfo()->GetActorForwardVector()*HitBoxForwardOffset;
	const FVector HitBoxLocation=GetAvatarActorFromActorInfo()->GetActorLocation()+ForwardVector+FVector(0.f,0.f,HitBoxElevationOffset);

	GetWorld()->OverlapMultiByChannel(OverlapResults,
		HitBoxLocation,
		FQuat::Identity,
		ECC_Visibility,
		Sphere,
		QueryParams,
		ResponseParams);

	TArray<AActor*> ActorsHit;
	for (const FOverlapResult& Result : OverlapResults)
	{
		if (!IsValid(Result.GetActor()))continue;
		ActorsHit.AddUnique(Result.GetActor());
	}
	
	if (bDrawDebugs)
	{
		DrawHitBoxOverlapDebugs(OverlapResults,HitBoxLocation);
	}
	return ActorsHit;
}

void ULT_Primary::SendHitReactEventToActors(const TArray<AActor*>& ActorsHit)
{
	for (AActor* HitActor  : ActorsHit)
	{
		FGameplayEventData Payload;
		Payload.Instigator=GetAvatarActorFromActorInfo();
		UAbilitySystemBlueprintLibrary::SendGameplayEventToActor(HitActor,LTTags::Events::Enemy::HitReact,Payload);
	}
}

void ULT_Primary::DrawHitBoxOverlapDebugs(const TArray<FOverlapResult>& OverlapResults,
	const FVector& HitBoxLocation) const
{
	DrawDebugSphere(GetWorld(),HitBoxLocation,HitBoxRadius,16,FColor::Red,false,3.f);

	for (const FOverlapResult& OverlapResult : OverlapResults)
	{
		if (IsValid(OverlapResult.GetActor()))
		{
			FVector DebugLocation=OverlapResult.GetActor()->GetActorLocation();
			DebugLocation.Z += 100.f;
			DrawDebugSphere(GetWorld(),DebugLocation,30.f,10,FColor::Green,false,3.f);

		}
	}
}
