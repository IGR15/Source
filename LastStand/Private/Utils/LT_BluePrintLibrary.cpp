// Omar Sweiti


#include "Utils/LT_BluePrintLibrary.h"

#include "AbilitySystemBlueprintLibrary.h"
#include "Characters/LT_BaseCharacter.h"
#include "Engine/OverlapResult.h"
#include "Kismet/GameplayStatics.h"
#include "LTGamePlayTags/LTTags.h"

EHitDirection ULT_BluePrintLibrary::GetHitDirection(const FVector& TargetForward, const FVector& ToInstigator)
{
	const float Dot=FVector::DotProduct(TargetForward,ToInstigator);
	if (Dot<-0.5f)//backwards
	{
		return EHitDirection::Backward;
	}
	if (Dot<0.5f)
	{
		//Either Left or Right
		const FVector Cross=FVector::CrossProduct(TargetForward,ToInstigator);
		if (Cross.Z<0.f)
		{
			return EHitDirection::Left;
		}
		return EHitDirection::Right;
	}
	return EHitDirection::Forward;
}

FName ULT_BluePrintLibrary::GetHitDirectionName(const EHitDirection& Direction)
{
	switch (Direction)
	{
	case EHitDirection::Left: return FName("Left");
	case EHitDirection::Right: return FName("Right");
	case EHitDirection::Backward: return FName("Backward");
	case EHitDirection::Forward: return FName("Forward");
	default: return FName("None");
		
	}
}

FClosestActorWithTagResult ULT_BluePrintLibrary::FindClosestActorWithTag(const UObject* WorldContextObject,
	const FVector& Origin, const FName& Tag)
{
	TArray<AActor*> ActorsWithTag;
	UGameplayStatics::GetAllActorsWithTag(WorldContextObject,Tag,ActorsWithTag);

	float ClosestDistance=TNumericLimits<float>::Max();
	AActor* ClosestActor=nullptr;

	for (AActor* Actor : ActorsWithTag)
	{
		if (!IsValid(Actor))continue;
		ALT_BaseCharacter* BaseCharacter=Cast<ALT_BaseCharacter>(Actor);
		if (!IsValid(BaseCharacter)|| !BaseCharacter->IsAlive())continue;

		const float Distance=FVector::Dist(Origin,Actor->GetActorLocation());
		if (Distance<ClosestDistance)
		{
			ClosestDistance=Distance;
			ClosestActor=Actor;
		}
	}
	FClosestActorWithTagResult Result;
	Result.Actor=ClosestActor;
	Result.Distance=ClosestDistance;

	return Result;
}

void ULT_BluePrintLibrary::SendDamageEventToPlayer(AActor* Target, const TSubclassOf<UGameplayEffect>& DamageEffect,
	FGameplayEventData& Payload, const FGameplayTag& DataTag, float Damage,UObject* OptionalParticleSystem)
{
	ALT_BaseCharacter* PlayerCharacter=Cast<ALT_BaseCharacter>(Target);
	if (!IsValid(PlayerCharacter)|| !PlayerCharacter->IsAlive())return;

	ULT_AttributeSet* AttributeSet=Cast<ULT_AttributeSet>(PlayerCharacter->GetAttributeSet());
	if (!IsValid(AttributeSet))return;

	const bool bLethal=AttributeSet->GetHealth()-Damage<=0.f;
	const FGameplayTag EventTag=bLethal ? LTTags::Events::Player::Death:LTTags::Events::Player::HitReact;

	Payload.OptionalObject=OptionalParticleSystem;
	
	UAbilitySystemBlueprintLibrary::SendGameplayEventToActor(PlayerCharacter,EventTag,Payload);

	UAbilitySystemComponent* TargetASC=PlayerCharacter->GetAbilitySystemComponent();
	if (!IsValid(TargetASC))return;

	FGameplayEffectContextHandle ContextHandle= TargetASC->MakeEffectContext();
	FGameplayEffectSpecHandle SpecHandle=TargetASC->MakeOutgoingSpec(DamageEffect,1.f,ContextHandle);

	UAbilitySystemBlueprintLibrary::AssignTagSetByCallerMagnitude(SpecHandle,DataTag,-Damage);
	
	TargetASC->ApplyGameplayEffectSpecToSelf(*SpecHandle.Data.Get());
	
}

TArray<AActor*> ULT_BluePrintLibrary::HitBoxOverlapTest(AActor* AvatarActor,float HitBoxRadius,float HitBoxForwardOffset,
	float HitBoxElevationOffset,bool bDrawDebugs)
{
	if (!IsValid(AvatarActor))return TArray<AActor*>();
	
	/*
	TArray<AActor*> ActorsToIgnore;
	ActorsToIgnore.Add(AvatarActor);*/

	// Ensure that the overlap test ignores the avatar actor 
	FCollisionQueryParams QueryParams;
	QueryParams.AddIgnoredActor(AvatarActor);

	FCollisionResponseParams ResponseParams;
	ResponseParams.CollisionResponse.SetAllChannels(ECR_Ignore);
	ResponseParams.CollisionResponse.SetResponse(ECC_Pawn,ECR_Block);

	TArray<FOverlapResult> OverlapResults;
	FCollisionShape Sphere=FCollisionShape::MakeSphere(HitBoxRadius);

	const FVector ForwardVector=AvatarActor->GetActorForwardVector()*HitBoxForwardOffset;
	const FVector HitBoxLocation=AvatarActor->GetActorLocation()+ForwardVector+FVector(0.f,0.f,HitBoxElevationOffset);
	UWorld* World = GEngine->GetWorldFromContextObject(AvatarActor, EGetWorldErrorMode::LogAndReturnNull);
	if (!IsValid(World))return TArray<AActor*>();
	

	
	World->OverlapMultiByChannel(OverlapResults,
		HitBoxLocation,
		FQuat::Identity,
		ECC_Visibility,
		Sphere,
		QueryParams,
		ResponseParams);

	TArray<AActor*> ActorsHit;
	for (const FOverlapResult& Result : OverlapResults)
	{
		ALT_BaseCharacter* BaseCharacter=Cast<ALT_BaseCharacter>(Result.GetActor());
		if (!IsValid(BaseCharacter))continue;
		if (!BaseCharacter->IsAlive())continue;
		ActorsHit.AddUnique(BaseCharacter);
	}
	
	if (bDrawDebugs)
	{
		DrawHitBoxOverlapDebugs(AvatarActor,OverlapResults,HitBoxLocation,HitBoxRadius);
	}
	return ActorsHit;
}

void ULT_BluePrintLibrary::DrawHitBoxOverlapDebugs(const UObject* WorldContextObject,const TArray<FOverlapResult>& OverlapResults,
	const FVector& HitBoxLocation,float HitBoxRadius)
{
	UWorld* World = GEngine->GetWorldFromContextObject(WorldContextObject, EGetWorldErrorMode::LogAndReturnNull);
	if (!IsValid(World))return;
	DrawDebugSphere(World,HitBoxLocation,HitBoxRadius,16,FColor::Red,false,3.f);

	for (const FOverlapResult& OverlapResult : OverlapResults)
	{
		if (IsValid(OverlapResult.GetActor()))
		{
			FVector DebugLocation=OverlapResult.GetActor()->GetActorLocation();
			DebugLocation.Z += 100.f;
			DrawDebugSphere(World,DebugLocation,30.f,10,FColor::Green,false,3.f);

		}
	}
}
