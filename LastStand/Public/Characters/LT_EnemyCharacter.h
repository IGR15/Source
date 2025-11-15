// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "LT_BaseCharacter.h"
#include "LT_EnemyCharacter.generated.h"

class UAttributeSet;
class UAbilitySystemComponent;

UCLASS()
class LASTSTAND_API ALT_EnemyCharacter : public ALT_BaseCharacter
{
	GENERATED_BODY()

public:
	
	ALT_EnemyCharacter();
	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;

	virtual UAttributeSet* GetAttributeSet() const override;

	UPROPERTY(EditAnywhere,BlueprintReadOnly,Category="Ai")
	float AcceptenceRaidus{500.f};

	UFUNCTION(BlueprintImplementableEvent)
	float GetTimeLineLength();
	
	
	UPROPERTY(EditAnywhere,BlueprintReadOnly,Category="Ai")
	float MinAttackDelay{.1f};

	UPROPERTY(EditAnywhere,BlueprintReadOnly,Category="Ai")
	float MaxAttackDelay{.5f};

	virtual void HandleDeath() override;
	
	virtual void StopMovementUntilLanded() override;

protected:
	virtual void BeginPlay() override;


private:
	
	UFUNCTION()
	void EnableMovementOnLanded(const FHitResult& Hit);
	
	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UAbilitySystemComponent> AbilitySystemComponent;

	UPROPERTY()
	TObjectPtr<UAttributeSet>AttributeSet;
};
