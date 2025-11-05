// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "LT_BaseCharacter.h"
#include "LT_PlayerCharacter.generated.h"

class ULT_GamePlayAbility;
class UCameraComponent;
class USpringArmComponent;


UCLASS()
class LASTSTAND_API ALT_PlayerCharacter : public ALT_BaseCharacter
{
	GENERATED_BODY()
	
	ALT_PlayerCharacter();
	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;

	virtual UAttributeSet* GetAttributeSet() const override;

	virtual void PossessedBy(AController* NewController) override;
	virtual void OnRep_PlayerState() override;

public:

	UPROPERTY(EditDefaultsOnly, Category = "Combo")
	float ComboResetDelay = 1.0f;
	FTimerHandle ComboResetHandle;
	UFUNCTION(BlueprintCallable)
	void StartComboWindow(float Seconds = 2.f);
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Attack")
	TArray<UAnimMontage*> AttackMontages;

	UPROPERTY(BlueprintReadWrite)
	int32 ComboIndex = 0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Combat")
	bool bCanAttack=true;
	

	
	
	UFUNCTION(BlueprintCallable, Category = "Combat|Functions")
	UAnimMontage* GetNextComboMontage();
	
	UFUNCTION( BlueprintCallable,Category = "Combat|Functions")
	void ResetComboIndex();
	void OnComboTimeout();

	

	
private:
	
	
	UPROPERTY(VisibleAnywhere,Category="camera")
	TObjectPtr<USpringArmComponent> CameraBoom;

	UPROPERTY(VisibleAnywhere,Category="camera")
	TObjectPtr<UCameraComponent> FollowCamera;
};
