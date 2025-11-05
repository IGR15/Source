// Fill out your copyright notice in the Description page of Project Settings.


#include "LastStand/Public/Characters/LT_PlayerCharacter.h"
#include "AbilitySystemComponent.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "AbilitySystem/LT_AttributeSet.h"
#include "LastStand/Public/Player/LT_PlayerState.h"


// Sets default values
ALT_PlayerCharacter::ALT_PlayerCharacter()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	
	GetCapsuleComponent()->InitCapsuleSize(42.f,96.f);

	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	GetCharacterMovement()->bOrientRotationToMovement=true;
	GetCharacterMovement()->RotationRate=FRotator(0.f,540.f,0.f);
	GetCharacterMovement()->JumpZVelocity=500.f;
	GetCharacterMovement()->AirControl=0.35f;
	GetCharacterMovement()->MaxWalkSpeed=500.f;
	GetCharacterMovement()->MinAnalogWalkSpeed=20.f;
	GetCharacterMovement()->BrakingDecelerationWalking=2000.f;
	GetCharacterMovement()->BrakingDecelerationFalling=1500.f;

	CameraBoom=CreateDefaultSubobject<USpringArmComponent>("CameraBoom");
	CameraBoom->SetupAttachment(GetRootComponent());
	CameraBoom->TargetArmLength=600.f;
	CameraBoom->bUsePawnControlRotation=true;

	FollowCamera=CreateDefaultSubobject<UCameraComponent>("FollowCamera");
	FollowCamera->SetupAttachment(CameraBoom,USpringArmComponent::SocketName);
	FollowCamera->bUsePawnControlRotation=false;

	ComboResetDelay=2.f;
	Tags.Add(LaststandTags::Player);
}


UAbilitySystemComponent* ALT_PlayerCharacter::GetAbilitySystemComponent() const
{
	ALT_PlayerState* LTPlayerState=Cast<ALT_PlayerState>(GetPlayerState());
	if (!IsValid(LTPlayerState))return nullptr;

	return LTPlayerState->GetAbilitySystemComponent();
}

UAttributeSet* ALT_PlayerCharacter::GetAttributeSet() const
{
	ALT_PlayerState* LTPlayerState=Cast<ALT_PlayerState>(GetPlayerState());
	if (!IsValid(LTPlayerState))return nullptr;

	return LTPlayerState->GetAttributeSet();
}

void ALT_PlayerCharacter::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);

	if (!IsValid(GetAbilitySystemComponent())||!HasAuthority())return;

	GetAbilitySystemComponent()->InitAbilityActorInfo(GetPlayerState(),this);
	OnASCInitialized.Broadcast(GetAbilitySystemComponent(),GetAttributeSet());
	GiveStartUpAbilities();
	InitializeAttributes();

	ULT_AttributeSet* LT_AttributeSet=Cast<ULT_AttributeSet>(GetAttributeSet());
	if (!IsValid(LT_AttributeSet))return;
	GetAbilitySystemComponent()->GetGameplayAttributeValueChangeDelegate(LT_AttributeSet->GetHealthAttribute()).AddUObject(this,&ThisClass::OnHealthChanged);
}

void ALT_PlayerCharacter::OnRep_PlayerState()
{
	Super::OnRep_PlayerState();

	if (!IsValid(GetAbilitySystemComponent()))return;

	GetAbilitySystemComponent()->InitAbilityActorInfo(GetPlayerState(),this);
	OnASCInitialized.Broadcast(GetAbilitySystemComponent(),GetAttributeSet());

	ULT_AttributeSet* LT_AttributeSet=Cast<ULT_AttributeSet>(GetAttributeSet());
	if (!IsValid(LT_AttributeSet))return;
	GetAbilitySystemComponent()->GetGameplayAttributeValueChangeDelegate(LT_AttributeSet->GetHealthAttribute()).AddUObject(this,&ThisClass::OnHealthChanged);
}

void ALT_PlayerCharacter::StartComboWindow(float Seconds)
{
	GetWorldTimerManager().ClearTimer(ComboResetHandle);
	GetWorldTimerManager().SetTimer(
		ComboResetHandle, this,
		&ALT_PlayerCharacter::OnComboTimeout,
		Seconds, false);
}

UAnimMontage* ALT_PlayerCharacter::GetNextComboMontage() 
{
	

	if (AttackMontages.Num() == 0) return nullptr;

	// wrap if we’re past the end
	ComboIndex = ComboIndex % AttackMontages.Num();

	if (!AttackMontages.IsValidIndex(ComboIndex)) return nullptr;

	UAnimMontage* M = AttackMontages[ComboIndex];

	// prep next call
	ComboIndex = (ComboIndex + 1) % AttackMontages.Num();
	return M;

	/*if (ComboIndex>=AttackMontages.Num())
	{
		ResetComboIndex();
	}
	if (AttackMontages.IsValidIndex(Index))
	{
		if (UAnimMontage* M = AttackMontages[Index])
		{
			ComboIndex++;
			return M;
		}
		UE_LOG(LogTemp, Warning, TEXT("AttackMontages[%d] is null"), Index);
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Index %d is out of bounds (Num=%d)"), Index, AttackMontages.Num());
	}
	return nullptr;*/
}



void ALT_PlayerCharacter::ResetComboIndex()
{
	ComboIndex = 0;
	bCanAttack = true;
	UE_LOG(LogTemp, Log, TEXT("Combo index reset by ability delegate."));
}

void ALT_PlayerCharacter::OnComboTimeout()
{
	ResetComboIndex();
}

