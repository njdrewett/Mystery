// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/Character/PlayerActionsComponent.h"

#include <filesystem>

#include "GameFramework/Character.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/KismetMathLibrary.h"

// Sets default values for this component's properties
UPlayerActionsComponent::UPlayerActionsComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	
}


// Called when the game starts
void UPlayerActionsComponent::BeginPlay()
{
	Super::BeginPlay();

	Character = GetOwner<ACharacter>();

	MovementComponent = Character->GetCharacterMovement();

	if ( !Character->Implements<UMainPlayer>()) { return; }

	IMainPlayer = Cast<class IMainPlayer>(Character);
}


// Called every frame
void UPlayerActionsComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UPlayerActionsComponent::sprint() {
	if (!IMainPlayer->HasStamina(sprintCost)) {
		walk();
		return;
	}

	if (MovementComponent->Velocity.Equals(FVector::ZeroVector, 1)) { return; }
	MovementComponent->MaxWalkSpeed = sprintSpeed;

	OnSprintDelegate.Broadcast(sprintCost);
}

void UPlayerActionsComponent::walk() {
	MovementComponent->MaxWalkSpeed = walkSpeed;
}

void UPlayerActionsComponent::roll() {
	if (isRollActive) {return;}
	if (!IMainPlayer->HasStamina(rollCost)) { return; }

	isRollActive = true;

	OnRollDelegate.Broadcast(rollCost);

	FVector direction {Character->GetCharacterMovement()->Velocity.Length() < 1 ?
		Character->GetActorForwardVector() :
		Character->GetLastMovementInputVector()};

	FRotator newRotation {UKismetMathLibrary::MakeRotFromX(direction)};

	Character->SetActorRotation(newRotation);
	
	float duration { Character->PlayAnimMontage(rollAnimMotange) };

	FTimerHandle rollTimerHandle;

	Character->GetWorldTimerManager().SetTimer(
		rollTimerHandle,
		this, &UPlayerActionsComponent::RollAnimationFinished,
		duration, false);
	
}

void UPlayerActionsComponent::RollAnimationFinished() {

	isRollActive = false;
}

