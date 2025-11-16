// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "AbilitySystemInterface.h"
#include "AbilitySystem/LT_AttributeSet.h"
#include "LT_BaseCharacter.generated.h"


namespace LaststandTags
{
	extern LASTSTAND_API const FName Player; 
}

class UAttributeSet;
class UGameplayEffect;
class UGameplayAbility;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FASCInitialized,UAbilitySystemComponent* ,ASC,UAttributeSet*,AS);

UCLASS(Abstract)
class LASTSTAND_API ALT_BaseCharacter : public ACharacter,public IAbilitySystemInterface
{
	GENERATED_BODY()

public:
	
	ALT_BaseCharacter();
	virtual void GetLifetimeReplicatedProps(TArray<class FLifetimeProperty>& OutLifetimeProps) const override;

	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;
	virtual UAttributeSet* GetAttributeSet()const{return nullptr;}

	UPROPERTY(BlueprintAssignable)
	FASCInitialized OnASCInitialized;

	bool IsAlive() const{return bAlive;}
	void SetAlive(bool bAliveStatus){bAlive=bAliveStatus;}

	UFUNCTION(BlueprintCallable,Category="Death")
	virtual void HandleRespawn();

	UFUNCTION(BlueprintCallable)
	void ResetAttributes();

	UFUNCTION(BlueprintImplementableEvent)
	void RotateToTarget(AActor* RotateTarget);

	UPROPERTY(VisibleAnywhere,BlueprintReadOnly,Replicated)
	bool bIsBeingLaunched=false;
	
	virtual  void StopMovementUntilLanded();
	
	UPROPERTY(EditAnywhere,category="AI")
	float SearchRange=1000.f;
	
protected:
	void GiveStartUpAbilities();
	void InitializeAttributes();
	
	void OnHealthChanged(const FOnAttributeChangeData& AttributeChangeData);

	virtual void HandleDeath();
private:
	UPROPERTY(EditDefaultsOnly,Category="GT|Abilities")
	TArray<TSubclassOf<UGameplayAbility>>StartUpAbilities;

	UPROPERTY(EditDefaultsOnly,Category="GT|Effects")
	TSubclassOf<UGameplayEffect>InitializeAttributeEffect;

	UPROPERTY(EditDefaultsOnly,Category="GT|Effects")
	TSubclassOf<UGameplayEffect>ResetAttributesEffect;

	UPROPERTY(BlueprintReadOnly,meta=(AllowPrivateAccess="true"),Replicated)
	bool bAlive=true;


};
