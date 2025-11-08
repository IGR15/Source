// Omar Sweiti


#include "AbilitySystem/AbilityTasks/LT_WaitGamePlayEvent.h"

ULT_WaitGamePlayEvent* ULT_WaitGamePlayEvent::WaitGameplayEventToActorProxy(AActor* TargetActor, FGameplayTag EventTag,
	bool OnlyTriggerOnce, bool OnlyMatchExact)
{
	ULT_WaitGamePlayEvent* MyObj = NewObject<ULT_WaitGamePlayEvent>();
	MyObj->SetAbilityActor(TargetActor);
	MyObj->Tag = EventTag;
	MyObj->OnlyTriggerOnce = OnlyTriggerOnce;
	MyObj->OnlyMatchExact = OnlyMatchExact;
	return MyObj;
}

void ULT_WaitGamePlayEvent::StartActivation()
{
	Activate();
}
