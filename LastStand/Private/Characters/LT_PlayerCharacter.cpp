// Fill out your copyright notice in the Description page of Project Settings.


#include "LastStand/Public/Characters/LT_PlayerCharacter.h"
#include "AbilitySystemComponent.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "AbilitySystem/Abilities/LT_GamePlayAbility.h"
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
}

void ALT_PlayerCharacter::OnRep_PlayerState()
{
	Super::OnRep_PlayerState();

	if (!IsValid(GetAbilitySystemComponent()))return;

	GetAbilitySystemComponent()->InitAbilityActorInfo(GetPlayerState(),this);
	OnASCInitialized.Broadcast(GetAbilitySystemComponent(),GetAttributeSet());
}
UAnimMontage* ALT_PlayerCharacter::GetNextComboMontage(int32 Index)const
{
	if (AttackMontages.IsValidIndex(Index))
	{
		return AttackMontages[Index];
	}
	return nullptr;
}
void ALT_PlayerCharacter::ResetComboIndex()
{
	ComboIndex = 0;
	bCanAttack = true;
	UE_LOG(LogTemp, Log, TEXT("Combo index reset by ability delegate."));
}

