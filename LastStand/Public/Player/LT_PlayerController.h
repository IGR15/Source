// Omar Sweiti

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "LT_PlayerController.generated.h"

/**
 * 
 */
struct FGameplayTag;
class UInputMappingContext;
class UInputAction;
struct FInputActionValue;
UCLASS()
class LASTSTAND_API ALT_PlayerController : public APlayerController
{
	GENERATED_BODY()
protected:
	virtual void SetupInputComponent() override;

private:
	UPROPERTY(EditDefaultsOnly,Category="GT|Input")
	TArray<TObjectPtr<UInputMappingContext>> InputMappingContexts;

	UPROPERTY(EditDefaultsOnly,Category="GT|Input|Movement")
	TObjectPtr<UInputAction>JumpAction;

	UPROPERTY(EditDefaultsOnly,Category="GT|Input|Movement")
	TObjectPtr<UInputAction>MoveAction;

	UPROPERTY(EditDefaultsOnly,Category="GT|Input|Movement")
	TObjectPtr<UInputAction>LookAction;

	UPROPERTY(EditDefaultsOnly,Category="GT|Input|Abilities")
	TObjectPtr<UInputAction>PrimaryAction;

	UPROPERTY(EditDefaultsOnly,Category="GT|Input|Abilities")
	TObjectPtr<UInputAction>SecondaryAction;

	UPROPERTY(EditDefaultsOnly,Category="GT|Input|Abilities")
	TObjectPtr<UInputAction>TertiaryAction;

	

	void Jump();
	void StopJumping();
	void Move(const FInputActionValue& Value);
	void Look(const FInputActionValue& Value);
	void Primary();
	void Secondary();
	void Tertiary();

	void ActivateAbility(const FGameplayTag& AbilityTag)const;
	bool IsAlive()const;
};
