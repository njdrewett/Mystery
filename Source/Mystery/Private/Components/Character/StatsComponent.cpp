// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/Character/StatsComponent.h"
#include "Kismet/KismetMathLibrary.h"

// Sets default values for this component's properties
UStatsComponent::UStatsComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UStatsComponent::BeginPlay()
{
	Super::BeginPlay();	
}


// Called every frame
void UStatsComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UStatsComponent::ReduceHealth(float Amount) {

	UE_LOG(LogActorComponent, Warning, TEXT("'%s' Reducing health "), *GetNameSafe(this));
	ReduceStatByValue(Amount, Health, MaxHealth);
}

void UStatsComponent::ReduceStatByValue(float Amount, EStat stat, EStat maxStat) {
	float CurrentValue = Stats[stat];
	CurrentValue -= Amount;
	Stats[stat] = UKismetMathLibrary::FClamp(
		CurrentValue,
		0,
		Stats[maxStat]);
}

void UStatsComponent::ReduceStamina(float Amount) {
	UE_LOG(LogActorComponent, Warning, TEXT("'%s' Reducing Stamina "), *GetNameSafe(this));
	ReduceStatByValue(Amount, Stamina, MaxStamina);
}

void UStatsComponent::RegenerateStamina() {

	Stats[Stamina] = UKismetMathLibrary::FInterpTo_Constant(
		Stats[EStat::Stamina],
		Stats[EStat::MaxStamina],
		GetWorld()->DeltaTimeSeconds ,
		staminaRegenerationRate
		
		);
}

