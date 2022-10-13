// Fill out your copyright notice in the Description page of Project Settings.


#include "BasePawn.h"
#include "Components/CapsuleComponent.h"
#include "Kismet/GameplayStatics.h"
#include "DrawDebugHelpers.h"
#include "Projectile.h"
#include "HealthComponent.h"

// Sets default values
ABasePawn::ABasePawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	CapsuleComp = CreateDefaultSubobject<UCapsuleComponent>(TEXT("Capsule Component"));
	RootComponent = CapsuleComp;

	BaseMeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Base Mesh Component"));
	BaseMeshComp->SetupAttachment(RootComponent);

	TurrettMeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Turrett Mesh Component"));
	TurrettMeshComp->SetupAttachment(BaseMeshComp);

	ProjectileSpawnPointComp = CreateDefaultSubobject<USceneComponent>(TEXT("Projectile Spawn Point Component"));
	ProjectileSpawnPointComp->SetupAttachment(TurrettMeshComp);

	HealthComp = CreateDefaultSubobject<UHealthComponent>(TEXT("Health Component"));
}

void ABasePawn::HandleDestruction()
{
	//TODO: visual/audio destruction
}


void ABasePawn::Fire()
{
	AProjectile* Projectile = GetWorld()->SpawnActor<AProjectile>(ProjectileClass, ProjectileSpawnPointComp->GetComponentLocation(), ProjectileSpawnPointComp->GetComponentRotation());

	Projectile->SetOwner(this);
}

void ABasePawn::RotateTurret(FVector LookAtTarget)
{
	FVector ToTarget = LookAtTarget - TurrettMeshComp->GetComponentLocation();
	FRotator LookAtRotation = FRotator(0.0f, ToTarget.Rotation().Yaw, 0.0f);
	TurrettMeshComp->SetWorldRotation(	FMath::RInterpTo(TurrettMeshComp->GetComponentRotation(), 
										LookAtRotation, 
										UGameplayStatics::GetWorldDeltaSeconds(this), 
										5.0f) );
}



