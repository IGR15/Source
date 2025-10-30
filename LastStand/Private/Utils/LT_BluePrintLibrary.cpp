// Omar Sweiti


#include "Utils/LT_BluePrintLibrary.h"

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
