// Fill out your copyright notice in the Description page of Project Settings.


#include "Tank.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "Kismet/GameplayStatics.h"
#include "DrawDebugHelpers.h"


ATank::ATank()
{
    PrimaryActorTick.bCanEverTick = true;

    SpringArmComp = CreateAbstractDefaultSubobject<USpringArmComponent>(TEXT("Spring Arm Comp"));
    SpringArmComp->SetupAttachment(RootComponent);

    CameraComp = CreateAbstractDefaultSubobject<UCameraComponent>(TEXT("Camera Comp"));
    CameraComp->SetupAttachment(SpringArmComp);

    //movement
    Speed = 1000.0f;
    TurnRate = 120.0f;
}

// Called when the game starts or when spawned
void ATank::BeginPlay()
{
    Super::BeginPlay();

    TankPlayerController = Cast<APlayerController>(GetController());
}



// Called every frame
void ATank::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

    if (TankPlayerController)
    {
        FHitResult HitResult;
        TankPlayerController->GetHitResultUnderCursor(ECollisionChannel::ECC_Visibility, false, HitResult);

        DrawDebugSphere(GetWorld(), HitResult.ImpactPoint, 50.0f, 10, FColor(255, 0, 0, 255));
        RotateTurret(HitResult.ImpactPoint);
    }

}

// Called to bind functionality to input
void ATank::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
    Super::SetupPlayerInputComponent(PlayerInputComponent);

    PlayerInputComponent->BindAxis("MoveForward", this, &ATank::Move);
    PlayerInputComponent->BindAxis("Turn", this, &ATank::Turn);
    PlayerInputComponent->BindAction("Fire", IE_Pressed, this, &ATank::Fire);
}

void ATank::Move(float Value)
{
    //UE_LOG(LogTemp, Warning, TEXT("W and S scale input value: %f"), Value);
    float DeltaTime = UGameplayStatics::GetWorldDeltaSeconds(this);

    FVector DeltaLocation(0.f);
    DeltaLocation.X = Speed * Value;

    AddActorLocalOffset(DeltaLocation * DeltaTime, true);

}

void ATank::Turn(float Value)
{
    //UE_LOG(LogTemp, Warning, TEXT("W and S scale input value: %f"), Value);
    float DeltaTime = UGameplayStatics::GetWorldDeltaSeconds(this);

    FRotator DeltaRotation(0);
    DeltaRotation.Yaw = TurnRate * Value;

    AddActorLocalRotation(DeltaRotation * DeltaTime, true);
    

}

void ATank::HandleDestruction()
{
    Super::HandleDestruction();

    SetActorHiddenInGame(true);
    SetActorTickEnabled(false);

    GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Yellow, TEXT("YOU LOST!"));
}

