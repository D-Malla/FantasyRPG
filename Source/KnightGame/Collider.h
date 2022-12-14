// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Collider.generated.h"

class USphereComponent;

UCLASS()
class KNIGHTGAME_API ACollider : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ACollider();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UPROPERTY(VisibleAnywhere, Category = "Mesh")
	UStaticMeshComponent* StaticMeshComponent;

	UPROPERTY(VisibleAnywhere, Category = "Mesh")
	USphereComponent* SphereComponent;

	FORCEINLINE	UStaticMeshComponent* GetMeshComponent() const { return StaticMeshComponent; }
	FORCEINLINE void SetMeshComponent(UStaticMeshComponent* Mesh) { StaticMeshComponent = Mesh; }
	FORCEINLINE	USphereComponent* GetSphereComponent() const { return SphereComponent; }
	FORCEINLINE void SetSphereComponent(USphereComponent* Sphere) { SphereComponent = Sphere; }

};
