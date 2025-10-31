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

void ALT_PlayerCharacter::StartComboResetTimer()
{
 
	GetWorldTimerManager().ClearTimer(ComboResetTimerHandle);

	UE_LOG(LogTemp, Warning, TEXT("Starting combo reset timer for %f seconds"), ComboResetDelay);
	
		GetWorldTimerManager().ClearTimer(ComboResetTimerHandle);

		GetWorldTimerManager().SetTimer(
			ComboResetTimerHandle,
			this,
			&ALT_PlayerCharacter::ResetComboIndex,
			ComboResetDelay,
			false);
		OnComboReset.Broadcast();
	
	UE_LOG(LogTemp, Warning, TEXT("after combo reset timer for %f seconds"), ComboResetDelay);
}

/*void ALT_PlayerCharacter::ComboAttack()
{
	if (!bCanAttack || AttackMontages.Num() == 0) return;
	bCanAttack = false;

	UAnimMontage* MontageToPlay = AttackMontages[ComboIndex];
	if (!MontageToPlay) return;

	float Duration = PlayAnimMontage(MontageToPlay);
	if (UAnimInstance* AnimInstance = GetMesh()->GetAnimInstance())
	{
		AnimInstance->OnMontageEnded.AddDynamic(this, &ALT_PlayerCharacter::OnAttackMontageEnded);
	}

	ComboIndex = (ComboIndex + 1) % AttackMontages.Num();
}*/

UAnimMontage* ALT_PlayerCharacter::GetNextComboMontage(int32 Index)const
{
	if (AttackMontages.IsValidIndex(Index))
	{
		return AttackMontages[Index];
	}
	return nullptr;
	/*// Validation
	if (AttackMontages.Num() == 0 || !bCanAttack)
		return nullptr;

	// Lock attacks
	bCanAttack = false;

	// Cancel previous reset timer
	GetWorldTimerManager().ClearTimer(ComboResetTimerHandle);

	// Select montage safely
	UAnimMontage* SelectedMontage = AttackMontages.IsValidIndex(ComboIndex)
		? AttackMontages[ComboIndex]
		: nullptr;

	if (!SelectedMontage)
		return nullptr;

	// Advance combo index
	ComboIndex = (ComboIndex + 1) % AttackMontages.Num();

	// Schedule automatic reset
	GetWorldTimerManager().SetTimer(
		ComboResetTimerHandle,
		this,
		&ALT_PlayerCharacter::ResetComboIndex,
		ComboResetDelay,
		false
	);

	// Return only the pointer — no playback
	return SelectedMontage;*/
}

void ALT_PlayerCharacter::ResetComboIndex()
{
	ComboIndex = 0;
	bCanAttack = true;
	UE_LOG(LogTemp, Log, TEXT("Combo index reset by ability delegate."));
}

