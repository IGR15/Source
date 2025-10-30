// Omar Sweiti


#include "UI/LT_AttributeWidget.h"

void ULT_AttributeWidget::OnAttributeChange(const TTuple<FGameplayAttribute, FGameplayAttribute>& Pair,
	ULT_AttributeSet* AttributeSet)
{
	const float AttributeValue=Pair.Key.GetNumericValue(AttributeSet);
	const float MaxAttributeValue=Pair.Value.GetNumericValue(AttributeSet);

	BP_OnAttributeChange(AttributeValue,MaxAttributeValue);
}

bool ULT_AttributeWidget::MatchesAttribute(const TTuple<FGameplayAttribute, FGameplayAttribute>& Pair) const
{
	return Attribute==Pair.Key && MaxAttribute==Pair.Value;

}

