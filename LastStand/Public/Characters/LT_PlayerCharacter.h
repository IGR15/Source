// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "LT_BaseCharacter.h"
#include "LT_PlayerCharacter.generated.h"

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
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Attack")
	TArray<UAnimMontage*> AttackMontages;

	UPROPERTY()
	int32 ComboIndex = 0;

	UPROPERTY()
	bool bCanAttack = true;

	/*UFUNCTION(BlueprintCallable, Category = "Combat")
	void ComboAttack();
	*/

	
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Combat")
	float ComboResetDelay = 1.2f;

	
	UFUNCTION(BlueprintCallable, Category = "Combat|Functions")
	UAnimMontage* GetNextComboMontage(int32 Index)const;

	UFUNCTION(BlueprintCallable, Category = "Combat|Functions")
	void ResetComboIndex();
protected:
	FTimerHandle ComboResetTimerHandle;

	
private:
	
	
	UPROPERTY(VisibleAnywhere,Category="camera")
	TObjectPtr<USpringArmComponent> CameraBoom;

	UPROPERTY(VisibleAnywhere,Category="camera")
	TObjectPtr<UCameraComponent> FollowCamera;
};
