// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "BasePawn.generated.h"

UCLASS()
class TOONTANKS_API ABasePawn : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ABasePawn();

protected:

	void RotateTurret(FVector LookAtTarget);

	void Fire();

public:
	virtual void HandleDestruction();
	
private:

	UPROPERTY(VisibleAnywhere)
	class UCapsuleComponent* CapsuleComp;

	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* BaseMeshComp;

	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* TurrettMeshComp;

	UPROPERTY(VisibleAnywhere)
	USceneComponent* ProjectileSpawnPointComp;

	UPROPERTY(EditDefaultsOnly, Category = "Projectile")
	TSubclassOf<class AProjectile> ProjectileClass;

	UPROPERTY(VisibleAnywhere)
	class UHealthComponent* HealthComp;
};
