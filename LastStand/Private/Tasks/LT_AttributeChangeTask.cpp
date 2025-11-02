// Omar Sweiti


#include "Tasks/LT_AttributeChangeTask.h"

ULT_AttributeChangeTask* ULT_AttributeChangeTask::ListenForAttributeChange(
	UAbilitySystemComponent* AbilitySystemComponent, FGameplayAttribute Attribute)
{
	ULT_AttributeChangeTask* WaitForAttributeChangeTask=NewObject<ULT_AttributeChangeTask>();
	WaitForAttributeChangeTask->ASC=AbilitySystemComponent;
	WaitForAttributeChangeTask->AttributeToListenFor=Attribute;

	if (!IsValid(AbilitySystemComponent))
	{
		WaitForAttributeChangeTask->RemoveFromRoot();
		return nullptr;
	}
	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(Attribute).AddUObject(WaitForAttributeChangeTask,&ULT_AttributeChangeTask::AttributeChanged);
	return WaitForAttributeChangeTask;
}

void ULT_AttributeChangeTask::EndTask()
{
	if (ASC.IsValid())
	{
		ASC->GetGameplayAttributeValueChangeDelegate(AttributeToListenFor).RemoveAll(this);
	}
	SetReadyToDestroy();
	MarkAsGarbage();
}

void ULT_AttributeChangeTask::AttributeChanged(const FOnAttributeChangeData& Data)
{
	OnAttributeChanged.Broadcast(Data.Attribute,Data.NewValue,Data.OldValue);
}
