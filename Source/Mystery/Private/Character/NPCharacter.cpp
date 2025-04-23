// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/NPCharacter.h"
#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Player/PlayerCharacter.h"

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

	AIController = GetController<AAIController>();

	
	if (AIController) {
		BlackboardComponent = AIController->GetBlackboardComponent();
		if (InitialState) {
			BlackboardComponent->SetValueAsEnum("CurrentState", InitialState);
		}
	}

	GetWorld()->GetFirstPlayerController()->GetPawn<APlayerCharacter>()->
	StatsComponent->onHealthZeroDelegate.AddDynamic(this, &ANPCharacter::HandlePlayerDeath);
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
	UE_LOG(LogTemp, Warning, TEXT("Playing Random Attack"));
	Super::attack();

	CombatComponent->randomAttack();
}

float ANPCharacter::GetAnimationDuration() const {
	return CombatComponent->animationDuration;
}

float ANPCharacter::GetMeleeRange() const {
	if (StatsComponent != nullptr && StatsComponent->Stats.Contains(MeleeRange)) {
//		UE_LOG(LogActor, Warning, TEXT("'%s' returning melee range of %s "), *GetNameSafe(this), *FString::SanitizeFloat(StatsComponent->Stats[MeleeRange]));
		return StatsComponent->Stats[MeleeRange];
	}
//	UE_LOG(LogActor, Warning, TEXT("'%s' No stats details for melee range"), *GetNameSafe(this));
	return 0.0f;
}

void ANPCharacter::HandlePlayerDeath() {

	GetController<AAIController>()->GetBlackboardComponent()->SetValueAsEnum(
		"CurrentState", GameOver);
}	


