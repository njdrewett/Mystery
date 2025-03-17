// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/PlayerCharacter.h"

#include "Components/Combat/CombatComponent.h"
#include "Components/Combat/LockOnComponent.h"
#include "Components/Combat/TraceComponent.h"
#include "Engine/LocalPlayer.h"
#include "GameFramework/Controller.h"
#include "Player/Animation/PlayerAnimInstance.h"

// Sets default values
APlayerCharacter::APlayerCharacter():Super()
{
	// Components
	LockOnComponent = CreateDefaultSubobject<ULockOnComponent>(TEXT("LockOnComponent"));
	LockOnComponent->RegisterComponent();

	CombatComponent = CreateDefaultSubobject<UCombatComponent>(TEXT("CombatComponent"));
	CombatComponent->RegisterComponent();

	TraceComponent = CreateDefaultSubobject<UTraceComponent>(TEXT("TraceComponent"));
	TraceComponent->RegisterComponent();

}

// Called when the game starts or when spawned
void APlayerCharacter::BeginPlay()
{
	Super::BeginPlay();

	playerAnimInstance = Cast<UPlayerAnimInstance>(GetMesh()->GetAnimInstance());
}

// Called every frame
void APlayerCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

