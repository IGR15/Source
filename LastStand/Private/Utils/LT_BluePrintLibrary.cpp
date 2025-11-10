// Omar Sweiti


#include "Utils/LT_BluePrintLibrary.h"

#include "AbilitySystemBlueprintLibrary.h"
#include "Characters/LT_BaseCharacter.h"
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
	const FGameplayEventData& Payload, const FGameplayTag& DataTag, float Damage)
{
	ALT_BaseCharacter* PlayerCharacter=Cast<ALT_BaseCharacter>(Target);
	if (!IsValid(PlayerCharacter)|| !PlayerCharacter->IsAlive())return;

	ULT_AttributeSet* AttributeSet=Cast<ULT_AttributeSet>(PlayerCharacter->GetAttributeSet());
	if (!IsValid(AttributeSet))return;

	const bool bLethal=AttributeSet->GetHealth()-Damage<=0.f;
	const FGameplayTag EventTag=bLethal ? LTTags::Events::Player::Death:LTTags::Events::Player::HitReact;

	UAbilitySystemBlueprintLibrary::SendGameplayEventToActor(PlayerCharacter,EventTag,Payload);

	UAbilitySystemComponent* TargetASC=PlayerCharacter->GetAbilitySystemComponent();
	if (!IsValid(TargetASC))return;

	FGameplayEffectContextHandle ContextHandle= TargetASC->MakeEffectContext();
	FGameplayEffectSpecHandle SpecHandle=TargetASC->MakeOutgoingSpec(DamageEffect,1.f,ContextHandle);

	UAbilitySystemBlueprintLibrary::AssignTagSetByCallerMagnitude(SpecHandle,DataTag,-Damage);
	
	TargetASC->ApplyGameplayEffectSpecToSelf(*SpecHandle.Data.Get());
	
}
