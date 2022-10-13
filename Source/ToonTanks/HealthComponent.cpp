// Fill out your copyright notice in the Description page of Project Settings.


#include "HealthComponent.h"
#include "ToonTanksGameModeBase.h"
#include "Kismet/GameplayStatics.h"
#include "Tank.h"

// Sets default values for this component's properties
UHealthComponent::UHealthComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	MaxHealth = 100.f;
	
}


// Called when the game starts
void UHealthComponent::BeginPlay()
{
	Super::BeginPlay();

	Health = MaxHealth;

	GetOwner()->OnTakeAnyDamage.AddDynamic(this, &UHealthComponent::DamageTaken);
	
	ToonTanksGameModeBase = Cast<AToonTanksGameModeBase>(UGameplayStatics::GetGameMode(this));
}


// Called every frame
void UHealthComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}


void UHealthComponent::DamageTaken(AActor* DamagedActor, float Damage, const UDamageType* DamageType, class AController* Instigator, AActor* DamageCauser)
{
	Health -= Damage;

	UE_LOG(LogTemp, Warning, TEXT("%s is hitting %s's with %f points of damage. || %s's HEALTH :%f"), *DamageCauser->GetName(), *DamagedActor->GetName(), Damage, *DamagedActor->GetName(), Health);

	if (Cast<ATank>(DamagedActor))
	{ 
		FString HealthMsg = "TANK HEALTH :" + FString::SanitizeFloat(Health);;
		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Yellow, HealthMsg);
	}

	

	if (Health <= 0.f && ToonTanksGameModeBase)
	{
		ToonTanksGameModeBase->ActorDied(DamagedActor);
	}
}
