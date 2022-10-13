// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BasePawn.h"
#include "Tower.generated.h"

/**
 * 
 */
UCLASS()
class TOONTANKS_API ATower : public ABasePawn
{
	GENERATED_BODY()

public:
	ATower();

protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;

	virtual void HandleDestruction() override;

private:
	class ATank* Tank;

	UPROPERTY(EditAnywhere, Category="Turret Cannon")
	float TargetRange;

	bool IsTargetInRange();

	FTimerHandle FireRateTimerHandle;

	UPROPERTY(EditAnywhere, Category="Turret Cannon")
	float FireRate;

	void FireAtCondition();
};


