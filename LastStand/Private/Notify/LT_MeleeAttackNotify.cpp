// Omar Sweiti


#include "Notify/LT_MeleeAttackNotify.h"

#include "AbilitySystemBlueprintLibrary.h"
#include "KismetTraceUtils.h"
#include "Characters/LT_PlayerCharacter.h"
#include "Kismet/KismetMathLibrary.h"
#include "LTGamePlayTags/LTTags.h"

void ULT_MeleeAttackNotify::NotifyTick(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation,
                                       float FrameDeltaTime, const FAnimNotifyEventReference& EventReference)
{
	Super::NotifyTick(MeshComp, Animation, FrameDeltaTime, EventReference);

	if (!IsValid(MeshComp))return;
	if (!IsValid(MeshComp->GetOwner()))return;

	TArray<FHitResult>Hits=PerformSphereTrace(MeshComp);
	SendEventToActors(MeshComp,Hits);
	
}

TArray<FHitResult> ULT_MeleeAttackNotify::PerformSphereTrace(USkeletalMeshComponent* MeshComp)const
{
	TArray<FHitResult>OutHits;

	const FTransform SocketTransform= MeshComp->GetSocketTransform(SocketName);
	const FVector Start=SocketTransform.GetLocation();
	const FVector ExtendedSocketDirection=UKismetMathLibrary::GetForwardVector(SocketTransform.GetRotation().Rotator())*SocketExtensionOffset;
	const FVector End=Start-ExtendedSocketDirection;
	/*TArray<AActor*>ActorsToIgnore;
	ActorsToIgnore.Add(MeshComp->GetOwner());*/
	FCollisionQueryParams Params;
	Params.AddIgnoredActor(MeshComp->GetOwner());

	FCollisionResponseParams ResponseParams;
	ResponseParams.CollisionResponse.SetAllChannels(ECR_Ignore);
	ResponseParams.CollisionResponse.SetResponse(ECC_Pawn,ECR_Block);
	
	UWorld* World = GEngine->GetWorldFromContextObject(MeshComp, EGetWorldErrorMode::LogAndReturnNull);
	if (!IsValid(World))return OutHits;
	bool const bHit =  World->SweepMultiByChannel(
		OutHits,
		Start,
		End,
		FQuat::Identity,
		ECC_Visibility,
		FCollisionShape::MakeSphere(SphereTraceRadius),
		Params,ResponseParams);

	if (bDrawDebug)
	{
		DrawDebugSphereTraceMulti(
			World,
			Start,
			End,
			SphereTraceRadius,
			EDrawDebugTrace::ForDuration,
			bHit,
			OutHits,
			FColor::Red,
			FColor::Green,
			5.f
			);
		
	}
	
	return OutHits;
}

void ULT_MeleeAttackNotify::SendEventToActors(USkeletalMeshComponent* MeshComp,
	const TArray<FHitResult>& HitResults) const
{
	for (const FHitResult& Hit:HitResults)
	{
		ALT_PlayerCharacter* PlayerCharacter = Cast<ALT_PlayerCharacter>(Hit.GetActor());
		if (!IsValid(PlayerCharacter))continue;
		if (!PlayerCharacter->IsAlive())continue;
		UAbilitySystemComponent* ASC=PlayerCharacter->GetAbilitySystemComponent();
		if (!IsValid(ASC))continue;

		FGameplayEffectContextHandle ContextHandle= ASC->MakeEffectContext();
		ContextHandle.AddHitResult(Hit);

		FGameplayEventData Payload;
		Payload.Target=PlayerCharacter;
		Payload.ContextHandle=ContextHandle;
		Payload.Instigator=MeshComp->GetOwner();

		UAbilitySystemBlueprintLibrary::SendGameplayEventToActor(MeshComp->GetOwner(),LTTags::Events::Enemy::MeleeTraceHit,Payload);
	}
}
