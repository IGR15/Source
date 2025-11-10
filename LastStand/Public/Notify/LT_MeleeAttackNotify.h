// Omar Sweiti

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotifyState.h"
#include "LT_MeleeAttackNotify.generated.h"

/**
 * 
 */
UCLASS()
class LASTSTAND_API ULT_MeleeAttackNotify : public UAnimNotifyState
{
	GENERATED_BODY()

	virtual void NotifyTick(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float FrameDeltaTime, const FAnimNotifyEventReference& EventReference) override;

private:
	UPROPERTY(EditAnywhere)
	bool bDrawDebug=true;

	UPROPERTY(EditAnywhere)
	FName SocketName{"FX_Trail_01_R"};

	UPROPERTY(EditAnywhere)
	float SocketExtensionOffset{40.f};

	UPROPERTY(EditAnywhere)
	float SphereTraceRadius{60.f};

	TArray<FHitResult>PerformSphereTrace(USkeletalMeshComponent* MeshComp)const;

	void SendEventToActors(USkeletalMeshComponent* MeshComp,const TArray<FHitResult>& HitResults)const;
};
