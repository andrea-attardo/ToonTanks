// Fill out your copyright notice in the Description page of Project Settings.


#include "Tower.h"
#include "Tank.h"
#include "Kismet/GameplayStatics.h"
#include "TimerManager.h"

ATower::ATower()
{
    PrimaryActorTick.bCanEverTick = true;

    TargetRange = 2000.f;
    FireRate    = 2.f;
}



void ATower::BeginPlay()
{   
    Super::BeginPlay();
    
    Tank = Cast<ATank>(UGameplayStatics::GetPlayerPawn(this, 0));

    GetWorldTimerManager().SetTimer(FireRateTimerHandle, this, &ATower::FireAtCondition, FireRate, true);
}

void ATower::HandleDestruction()
{
    Super::HandleDestruction();
    Destroy();
}


void ATower::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

    if (IsTargetInRange())
    { 
        RotateTurret(Tank->GetActorLocation());
    }
}

void ATower::FireAtCondition()
{
    if (IsTargetInRange())
    {
        Fire();
    }
}

bool ATower::IsTargetInRange()
{ 
    if (Tank && !Tank->IsHidden())
    {
        float TurretTankDist = FVector::Dist(GetActorLocation(), Tank->GetActorLocation());

        return (TurretTankDist <= TargetRange);
    }
    return false;
}
