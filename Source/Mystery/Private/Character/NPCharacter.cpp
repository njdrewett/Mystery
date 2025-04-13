// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/NPCharacter.h"
#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"

// Sets default values
ANPCharacter::ANPCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void ANPCharacter::BeginPlay()
{
	Super::BeginPlay();

	if (GetController<AAIController>()) {
		BlackboardComponent = GetController<AAIController>()->GetBlackboardComponent();
		if (InitialState) {
			BlackboardComponent->SetValueAsEnum("CurrentState", InitialState);
		}
	}
	
}

// Called every frame
void ANPCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ANPCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

bool ANPCharacter::detectPawn(APawn* detected, APawn* toCheck) {
	UE_LOG(LogTemp, Warning, TEXT("Detected Pawn"));

	ENPCState currentState {
		static_cast<ENPCState>(BlackboardComponent->GetValueAsEnum("CurrentState"))
	};
	
	if (detected != toCheck || currentState != Idle) { return false; }

	UE_LOG(LogTemp, Warning, TEXT("Updating State"));
	BlackboardComponent->SetValueAsEnum("CurrentState", PlayerDetected);
	
	return false;

}

void ANPCharacter::attack() {
	Super::attack();

	CombatComponent->randomAttack();
	
}

float ANPCharacter::GetAnimationDuration() const {
	return CombatComponent->animationDuration;
}

float ANPCharacter::GetMeleeRange() const {
	if (StatsComponent != nullptr && StatsComponent->Stats.Contains(MeleeRange)) {
		return StatsComponent->Stats[MeleeRange];
	}
	return 0.0f;
}	


