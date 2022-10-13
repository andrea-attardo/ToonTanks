// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BasePawn.h"
#include "Tank.generated.h"

/**
 * 
 */
UCLASS()
class TOONTANKS_API ATank : public ABasePawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ATank();
	

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;


public:

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	virtual void SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) override;

	virtual void HandleDestruction() override;
	
	UFUNCTION()
	APlayerController* GetTankPlayerController() const { return TankPlayerController; }

private:
	
	UPROPERTY(VisibleAnywhere)
	class USpringArmComponent* SpringArmComp;

	UPROPERTY(VisibleAnywhere)
	class UCameraComponent* CameraComp;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement", meta = ( AllowPrivateAccess = "true" ))
	float Speed;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement", meta = ( AllowPrivateAccess = "true" ))
	float TurnRate;

	void Move(float Value);

	void Turn(float Value);

	APlayerController* TankPlayerController;

};
