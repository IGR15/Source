// Omar Sweiti


#include "Player/LT_PlayerController.h"
#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"
#include "GameFramework/Character.h"
#include "AbilitySystemComponent.h"
#include "AbilitySystemBlueprintLibrary.h"
#include "Characters/LT_BaseCharacter.h"
#include "LTGamePlayTags/LTTags.h"



void ALT_PlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();
	UEnhancedInputLocalPlayerSubsystem* InputSubsystem=ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer());
	if (!IsValid(InputSubsystem))return;
	for (UInputMappingContext* Context:InputMappingContexts)
	{
		InputSubsystem->AddMappingContext(Context,0);
	}
	UEnhancedInputComponent* EnhancedInputComponent=Cast<UEnhancedInputComponent>(InputComponent);
	if (!IsValid(EnhancedInputComponent))return;

	EnhancedInputComponent->BindAction(JumpAction,ETriggerEvent::Started,this,&ALT_PlayerController::Jump);
	EnhancedInputComponent->BindAction(JumpAction,ETriggerEvent::Completed,this,&ALT_PlayerController::StopJumping);

	EnhancedInputComponent->BindAction(MoveAction,ETriggerEvent::Triggered,this,&ALT_PlayerController::Move);
	EnhancedInputComponent->BindAction(LookAction,ETriggerEvent::Triggered,this,&ALT_PlayerController::Look);
	
	EnhancedInputComponent->BindAction(PrimaryAction,ETriggerEvent::Triggered,this,&ALT_PlayerController::Primary);
	EnhancedInputComponent->BindAction(SecondaryAction,ETriggerEvent::Started,this,&ALT_PlayerController::Secondary);
	EnhancedInputComponent->BindAction(TertiaryAction,ETriggerEvent::Started,this,&ALT_PlayerController::Tertiary);
}

void ALT_PlayerController::Jump()
{
	if (!IsValid(GetCharacter()))return;
	if (!IsAlive())return;

	GetCharacter()->Jump();
}

void ALT_PlayerController::StopJumping()
{
	if (!IsValid(GetCharacter()))return;
	if (!IsAlive())return;

	GetCharacter()->StopJumping();
}

void ALT_PlayerController::Move(const FInputActionValue& Value)
{
	if (!IsValid(GetPawn()))return;
	if (!IsAlive())return;

	const FVector2D MovementVector=Value.Get<FVector2D>();

	//find which way is forward
	const FRotator YawRotation(0.f,GetControlRotation().Yaw,0.f);
	const FVector ForwardDirection=FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
	const FVector RightDirection=FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

	GetPawn()->AddMovementInput(ForwardDirection,MovementVector.Y);
	GetPawn()->AddMovementInput(RightDirection,MovementVector.X);
}

void ALT_PlayerController::Look(const FInputActionValue& Value)
{
	if (!IsAlive())return;
	const FVector2D LookAxisVector=Value.Get<FVector2D>();

	AddYawInput(LookAxisVector.X);
	AddPitchInput(LookAxisVector.Y);
}

void ALT_PlayerController::Primary()
{
	ActivateAbility(LTTags::LTAbilities::Primary);
}

void ALT_PlayerController::Secondary()
{
	ActivateAbility(LTTags::LTAbilities::Secondary);
}

void ALT_PlayerController::Tertiary()
{
	ActivateAbility(LTTags::LTAbilities::Tertiary);
}

void ALT_PlayerController::ActivateAbility(const FGameplayTag& AbilityTag) const
{
	if (!IsAlive())return;
	UAbilitySystemComponent* ASC= UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(GetPawn());
	if (!IsValid(ASC))return;
	ASC->TryActivateAbilitiesByTag(AbilityTag.GetSingleTagContainer());
}

bool ALT_PlayerController::IsAlive()const
{
	ALT_BaseCharacter* BaseCharacter=Cast<ALT_BaseCharacter>(GetPawn());
	if (!IsValid(BaseCharacter))return false;
	return BaseCharacter->IsAlive();
}
