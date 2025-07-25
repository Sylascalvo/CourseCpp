// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "SCharacter.generated.h"

class UCameraComponent;
class USpringArmComponent;
class USInteractionComponent;
class UAnimMontage;
class USAttributeComponent;

UCLASS()
class COURSECPP_API ASCharacter : public ACharacter
{
	GENERATED_BODY()

protected:

	UPROPERTY(EditAnywhere, Category = "Attack")
	TSubclassOf<AActor> ProjectileClass;

	UPROPERTY(EditAnywhere, Category = "Attack")
	TSubclassOf<AActor> BlackHoleProjectileClass;

	UPROPERTY(EditAnywhere, Category = "Attack")
	TSubclassOf<AActor> DashProjectileClass;

	UPROPERTY(EditAnywhere, Category = "Attack")
	UAnimMontage* AttackAnim;

	FTimerHandle TimerHandle_PrimaryAttack;
	FTimerHandle TimerHandle_BlackHoleAttack;
	FTimerHandle TimerHandle_Dash;

	UPROPERTY(EditDefaultsOnly, Category = "Attack")
	float AttackAnimDelay;




	UPROPERTY(VisibleAnywhere)
	USpringArmComponent* SpringArmComp;

	UPROPERTY(EditDefaultsOnly)
	UCameraComponent* CameraComp;

	UPROPERTY(EditDefaultsOnly)
	USInteractionComponent* InteractionComp;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	USAttributeComponent* AttributeComp;




	void MoveForward(float Value);

	void MoveRight(float Value);
	
	void PrimaryAttack_TimeElapsed();
	void BlackHoleAttack_TimeElapsed();
	void Dash_TimeElapsed();
	

	// Re-use spawn logic between attacks
	void SpawnProjectile(TSubclassOf<AActor> ClassToSpawn);

	void PrimaryInteract();
	void PrimaryAttack();
	void Dash();
	void BlackHoleAttack();

	UFUNCTION()
	void OnHealthChanged(AActor* InstigatorActor, USAttributeComponent* OwningComp, float NewHealth, float Delta);

	virtual void PostInitializeComponents() override;

public:	
	
	ASCharacter();

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};