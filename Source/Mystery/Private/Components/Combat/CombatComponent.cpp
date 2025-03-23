// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/Combat/CombatComponent.h"

#include "Character/GameCharacter.h"
#include "GameFramework/Character.h"
#include "Player/MainPlayer.h"

// Sets default values for this component's properties
UCombatComponent::UCombatComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ... 
	characterReference = GetOwner<ACharacter>();
}


// Called when the game starts
void UCombatComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UCombatComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UCombatComponent::attack() {
	UE_LOG(LogTemp, Warning, TEXT("Combat activate"));
	if (!canAttack) { return ;}

	IMainPlayer* mainPlayer = Cast<IMainPlayer>(characterReference);
	if (!mainPlayer || !mainPlayer->HasStamina(staminaCost)) {
		UE_LOG(LogTemp, Warning, TEXT("Not enough stamina to attack"));
		return;
	}
	
	canAttack = false;

	if (attackMontages.IsEmpty()) {
		UE_LOG(LogTemp, Warning, TEXT("No animation montages to play for attack  %s"), *GetOwner()->GetName());
		return;
	}
	
	characterReference->PlayAnimMontage(attackMontages[comboCounter++]);
	if (comboCounter > attackMontages.Num()-1) {
		comboCounter = 0;
	}
	OnAttackPerformedDelegate.Broadcast(staminaCost);
}

void UCombatComponent::resetAttack() {
	canAttack = true;
}

