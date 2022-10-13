// Fill out your copyright notice in the Description page of Project Settings.


#include "ToonTanksGameModeBase.h"
#include "Kismet/GameplayStatics.h"
#include "Tank.h"
#include "Tower.h"
#include "ToonTanksPlayerController.h"

void AToonTanksGameModeBase::BeginPlay()
{
    Super::BeginPlay();
    HandleGameStart();
  
}

void AToonTanksGameModeBase::ActorDied(AActor* DeadActor)
{
    if (DeadActor == Tank)
    {
        Tank->HandleDestruction();
        if (ToonTanksPlayerController)
        {
            ToonTanksPlayerController->SetPlayerEnableState(false);

            GameOver(false);
        }

    }
    else if (ATower* DeadTower = Cast<ATower>(DeadActor))
    {
        DeadTower->HandleDestruction();
        --TargetTower;

        if (TargetTower == 0)
        {
            GameOver(true);
        }
    }
}

void AToonTanksGameModeBase::HandleGameStart()
{
    Tank = Cast<ATank>(UGameplayStatics::GetPlayerPawn(this, 0));
    ToonTanksPlayerController = Cast<AToonTanksPlayerController>(UGameplayStatics::GetPlayerController(this, 0));

    TargetTower  = GetTargetTowerCount();

    StartGame();

    if(ToonTanksPlayerController)
    { 
        ToonTanksPlayerController->SetPlayerEnableState(false);

        FTimerHandle PlayerEnabledTimerHandle;

        FTimerDelegate PlayerEnableStateInputDelegate = FTimerDelegate::CreateUObject(ToonTanksPlayerController, &AToonTanksPlayerController::SetPlayerEnableState, true);

        GetWorldTimerManager().SetTimer(PlayerEnabledTimerHandle, PlayerEnableStateInputDelegate, GameStartDelay, false);
    }
}

int32 AToonTanksGameModeBase::GetTargetTowerCount()
{
    TArray<AActor*> Towers;
    UGameplayStatics::GetAllActorsOfClass(this, ATower::StaticClass(), Towers);


    return Towers.Num();
}
