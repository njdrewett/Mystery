// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/PlayerCharacter.h"

#include "Components/Combat/CombatComponent.h"
#include "Components/Combat/LockOnComponent.h"
#include "Components/Combat/TraceComponent.h"
#include "Engine/LocalPlayer.h"
#include "GameFramework/Controller.h"
#include "Player/Animation/PlayerAnimInstance.h"

// Sets default values
APlayerCharacter::APlayerCharacter() {
	// Components
	LockOnComponent = CreateDefaultSubobject<ULockOnComponent>(TEXT("LockOnComponent"));

	PlayerActionsComponent = CreateDefaultSubobject<UPlayerActionsComponent>(TEXT("PlayerActionsComponent"));

	BlockComponent = CreateDefaultSubobject<UBlockComponent>(TEXT("BlockComponent"));
}

// Called when the game starts or when spawned
void APlayerCharacter::BeginPlay() {
	Super::BeginPlay();

	playerAnimInstance = Cast<UPlayerAnimInstance>(GetMesh()->GetAnimInstance());
}

// Called every frame
void APlayerCharacter::Tick(float DeltaTime) {
	Super::Tick(DeltaTime);
}

bool APlayerCharacter::HasStamina(float cost) const {
	if (!StatsComponent || !StatsComponent->Stats.Contains(Stamina)) {
		UE_LOG(LogActor, Warning, TEXT("'%s' No stats details for Stamina"), *GetNameSafe(this));
		return false;
	}

	return (StatsComponent->Stats[Stamina] > cost);
}

void APlayerCharacter::EndLockOnWithActor(AActor* actorReference) {
	if (LockOnComponent->GetCurrentActorTarget() != actorReference) { return; }

	LockOnComponent->endLockOn();
}

bool APlayerCharacter::CanTakeDamage(AActor* attacker) {
	if (PlayerActionsComponent->isRollActive) { return false; }

	if (playerAnimInstance->isBlocking) {
		return BlockComponent->Check(attacker);
	}
	return true;
}
