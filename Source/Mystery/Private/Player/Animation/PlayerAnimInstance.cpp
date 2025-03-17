// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/Animation/PlayerAnimInstance.h"
#include "KismetAnimationLibrary.h"

void UPlayerAnimInstance::updateLockOnTarget(AActor* lockonTarget) {

	isLockOnMovement = IsValid(lockonTarget);
	if (isLockOnMovement) {	
		UE_LOG(LogTemp, Warning, TEXT("Valid target in update Lockon Target %s"),*lockonTarget->GetName()); 
	} else {
		UE_LOG(LogTemp, Warning, TEXT("Invalid target in update Lockon Target")); 
	}
}

void UPlayerAnimInstance::updateDirection() {
	APawn* pawnReference{ TryGetPawnOwner()};

	if (!IsValid(pawnReference)) {		return;	}

	if (!isLockOnMovement) {	return;	}

	currentDirection = UKismetAnimationLibrary::CalculateDirection(
		pawnReference->GetVelocity(),
		pawnReference->GetActorRotation()
	);
	
}