// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/GameCharacter.h"

// Sets default values
AGameCharacter::AGameCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	// Components
	StatsComponent = CreateDefaultSubobject<UStatsComponent>(TEXT("StatsComponent"));
	//StatsComponent->RegisterComponent();

}

// Called when the game starts or when spawned
void AGameCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AGameCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AGameCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

float AGameCharacter::GetDamage() const {
	if (!StatsComponent || !StatsComponent->Stats.Contains(Strength)) {
		UE_LOG(LogActor, Warning, TEXT("'%s' No stats details for strength"), *GetNameSafe(this));
		return 0;
	}
	return StatsComponent->Stats[Strength];
}
