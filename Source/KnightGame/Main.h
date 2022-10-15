// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Main.generated.h"

class AItem;
class AWeapon;
class UAnimMontage;
class UCameraComponent;
class UParticleSystem;
class USoundCue;
class USpringArmComponent;

UENUM(BlueprintType)
enum class EMovementStatus : uint8
{
	EMS_Normal			UMETA(DisplayName = "Normal"),
	EMS_Sprinting		UMETA(DisplayName = "Sprinting"),

	EMS_MAX				UMETA(DisplayName = "DefaultMAX")
};

UENUM(BlueprintType)
enum class EStaminaStatus : uint8
{
	ESS_Normal					UMETA(DisplayName = "Normal"),
	ESS_BelowMinimum			UMETA(DisplayName = "BelowMinimum"),
	ESS_Exhausted				UMETA(DisplayName = "Exhausted"),
	ESS_ExhaustedRecovering		UMETA(DisplayName = "ExhaustedRecovering"),

	ESS_MAX						UMETA(DisplayName = "DefaultMAX")
	
};

UCLASS()
class KNIGHTGAME_API AMain : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AMain();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Combat")
	UParticleSystem* HitParticles;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Combat")
	USoundCue* HitSound;

	TArray<FVector> PickupLocations;

	UFUNCTION(BlueprintCallable)
	void ShowPickupLocations();

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Enums")
	EMovementStatus MovementStatus;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Enums")
	EStaminaStatus StaminaStatus;

	FORCEINLINE void SetStaminaStatus(EStaminaStatus Status) { StaminaStatus = Status; }

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement")
	float StaminaDrainRate;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement")
	float MinSprintStamina;
	
	// Set movement status and running speed
	void SetMovementStatus(EMovementStatus Status);

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Running")
	float RunningSpeed;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Running")
	float SprintingSpeed;

	bool bShiftKeyDown;

	// Press down to enable sprinting
	void ShiftKeyDown();

	// Released to stop sprinting
	void ShiftKeyUp();

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Camera", meta = (AllowPrivateAccess = "true"))
	USpringArmComponent* SpringArmComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Camera", meta = (AllowPrivateAccess = "True"))
	UCameraComponent* CameraComponent;
	
	// Base turn rates to scale turning functions for the camera
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Camera")
	float BaseTurnRate;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Camera")
	float BaseLookUpRate;

	/**
	 *
	 * Player Stats
	 *
	 */

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Player Stats")
	float MaxHealth;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Player Stats")
	float Health;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Player Stats")
	float MaxStamina;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Player Stats")
	float Stamina;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Player Stats")
	int32 Coins;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Anims")
	UAnimMontage* CombatMontage;
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	// Called for forwards/backwards input
	void MoveForward(float Value);

	// Called for side to side input
	void MoveRight(float Value);

	// Called to look up/down at a given rate
	// @param Rate This is a normalized rate, ie. 1.0 means 100% of desired look up/down rate
	void TurnAtRate(float Rate);
	
	void LookUpAtRate(float Rate);

	bool bLMBDown;
	
	void LMBDown();
	
	void LMBUp();

	FORCEINLINE USpringArmComponent* GetSpringArm() const { return SpringArmComponent; }
	FORCEINLINE UCameraComponent* GetCamera() const { return CameraComponent; }
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Items")
	AWeapon* EquippedWeapon;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Items")
	class AItem* ActiveOverlappingItem;

	void SetEquippedWeapon(AWeapon* WeaponToSet);
	FORCEINLINE AWeapon* GetEquippedWeapon() { return EquippedWeapon; }
	FORCEINLINE void SetActiveOverlappingItem(AItem* Item) { ActiveOverlappingItem = Item; }

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Anims")
	bool bAttacking;

	void Attack();

	UFUNCTION(BlueprintCallable)
	void AttackEnd();

	void DecrementHealth(float Amount);

	void IncrementCoins(int32 Amount);

	void Die();

	UFUNCTION(BlueprintCallable)
	void PlaySwingSound();
};

