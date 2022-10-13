// Fill out your copyright notice in the Description page of Project Settings.


#include "Projectile.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/DamageType.h"

// Sets default values
AProjectile::AProjectile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
    
    ProjectileMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Projectile Mesh Comp"));
    RootComponent = ProjectileMesh;

    ProjectileMovComp = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("Projectile Movement Comp"));

    ProjectileMovComp->InitialSpeed = 500.f;
    ProjectileMovComp->MaxSpeed = 500.f;

    Damage = 50.f;
}

void AProjectile::BeginPlay()
{
    Super::BeginPlay();

    ProjectileMesh->OnComponentHit.AddDynamic(this, &AProjectile::OnHit);
}

void AProjectile::OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& HitResult)
{
    //UE_LOG(LogTemp, Warning, TEXT("Component: %s of the Actor: %s IS HITTING Component %s of the Actor %s."), *HitComp->GetName(), *HitComp->GetOwner()->GetName(), *OtherComp->GetName(), *OtherActor->GetName());

    auto ProjectileOwner = GetOwner();
    if (ProjectileOwner && OtherActor && (OtherActor != this) && (OtherActor != ProjectileOwner))
    { 
        UGameplayStatics::ApplyDamage(OtherActor, Damage, ProjectileOwner->GetInstigatorController(), ProjectileOwner, UDamageType::StaticClass());

        Destroy();
    }
}



