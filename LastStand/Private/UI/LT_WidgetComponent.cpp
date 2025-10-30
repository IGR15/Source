// Omar Sweiti


#include "UI/LT_WidgetComponent.h"
#include "AbilitySystem/LT_AbilitySystemComponent.h"
#include "AbilitySystem/LT_AttributeSet.h"
#include "Blueprint/WidgetTree.h"
#include "Characters/LT_BaseCharacter.h"
#include "UI/LT_AttributeWidget.h"


void ULT_WidgetComponent::BeginPlay()
{
	Super::BeginPlay();

	InitAbilitySystemData();
	if (!IsASCInitialized())
	{
		BaseCharacter->OnASCInitialized.AddDynamic(this,&ThisClass::OnASCInitialized);
		return;
	}
	InitializeAttributesDelegate();
}

void ULT_WidgetComponent::InitAbilitySystemData()
{
	BaseCharacter=Cast<ALT_BaseCharacter>(GetOwner());
	AttributeSet=Cast<ULT_AttributeSet>(BaseCharacter->GetAttributeSet());

	AbilitySystemComponent=Cast<ULT_AbilitySystemComponent>(BaseCharacter->GetAbilitySystemComponent());
}

bool ULT_WidgetComponent::IsASCInitialized() const
{
	return AbilitySystemComponent.IsValid()&&AttributeSet.IsValid();
}

void ULT_WidgetComponent::InitializeAttributesDelegate()
{
	if (!AttributeSet->bAttributeInitialized)
	{
		AttributeSet->OnAttributeInitializedDelegate.AddDynamic(this,&ThisClass::BindToAttributeChanges);
	}
	else
	{
		BindToAttributeChanges();
	}
}

void ULT_WidgetComponent::BindWidgetToAttributeChanges(UWidget* WidgetObject,
	const TTuple<FGameplayAttribute, FGameplayAttribute>& Pair) const
{
	ULT_AttributeWidget* AttributeWidget =Cast<ULT_AttributeWidget>(WidgetObject);
	if (!IsValid(AttributeWidget))return;
	if (!AttributeWidget->MatchesAttribute(Pair))return;

	AttributeWidget->OnAttributeChange(Pair,AttributeSet.Get());

	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(Pair.Key).AddLambda([this,AttributeWidget,&Pair](const FOnAttributeChangeData& AttributeChangeData)
	{
		AttributeWidget->OnAttributeChange(Pair,AttributeSet.Get());

	});
}

void ULT_WidgetComponent::OnASCInitialized(UAbilitySystemComponent* ASC, UAttributeSet* AS)
{
	AbilitySystemComponent=Cast<ULT_AbilitySystemComponent>(ASC);
	AttributeSet=Cast<ULT_AttributeSet>(AS);

	if (!IsASCInitialized())return;
	
	InitializeAttributesDelegate();
}

void ULT_WidgetComponent::BindToAttributeChanges()
{
	
	for (const TTuple<FGameplayAttribute,FGameplayAttribute>& Pair : AttributeMap)
	{
		BindWidgetToAttributeChanges(GetUserWidgetObject(),Pair);// fof checking the owned Widget Object
		GetUserWidgetObject()->WidgetTree->ForEachWidget([this,&Pair](UWidget* ChildWidget)
		{
			BindWidgetToAttributeChanges(ChildWidget,Pair);
		});
	}
}
