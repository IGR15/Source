// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "LT_BaseCharacter.h"
#include "LT_PlayerCharacter.generated.h"

class ULT_GamePlayAbility;
class UCameraComponent;
class USpringArmComponent;

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnComboReset);

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
	
	UPROPERTY(BlueprintAssignable, Category = "Combo")
	FOnComboReset OnComboReset;

	UFUNCTION(BlueprintCallable, Category = "Combo")
	void StartComboResetTimer();
	
	FTimerHandle ComboResetTimerHandle;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Attack")
	TArray<UAnimMontage*> AttackMontages;

	UPROPERTY()
	int32 ComboIndex = 0;

	UPROPERTY()
	bool bCanAttack=true;
	

	/*UFUNCTION(BlueprintCallable, Category = "Combat")
	void ComboAttack();
	*/
	
	UFUNCTION(BlueprintCallable, Category = "Combat|Functions")
	UAnimMontage* GetNextComboMontage(int32 Index)const;

	UFUNCTION( Category = "Combat|Functions")
	void ResetComboIndex();
protected:
	

	
private:
	
	
	UPROPERTY(VisibleAnywhere,Category="camera")
	TObjectPtr<USpringArmComponent> CameraBoom;

	UPROPERTY(VisibleAnywhere,Category="camera")
	TObjectPtr<UCameraComponent> FollowCamera;
};
