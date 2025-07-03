// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/Combat/LockOnComponent.h"

#include "Character/LockOnable.h"
#include "GameFramework/Character.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Kismet/KismetMathLibrary.h"

// Sets default values for this component's properties
ULockOnComponent::ULockOnComponent() {
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
}


// Called when the game starts
void ULockOnComponent::BeginPlay() {
	Super::BeginPlay();

	ownerCharacter = GetOwner<ACharacter>();

	playerController = GetWorld()->GetFirstPlayerController();

	characterMovementComponent = ownerCharacter->GetCharacterMovement();

	springArmComponent = ownerCharacter->GetComponentByClass<USpringArmComponent>();
}

void ULockOnComponent::toggleLockOn(float traceRadius) {
	if (IsValid(currentTargetActor)) {
		endLockOn();
	}
	else {
		startLockOn(traceRadius);
	}
}


void ULockOnComponent::startLockOn(float traceRadius) {
	UE_LOG(LogTemp, Warning, TEXT("LockOn Started"));

	FHitResult outResult;
	const FVector currentLocation{ownerCharacter->GetActorLocation()};

	const FCollisionShape sphereCollisionShape{FCollisionShape::MakeSphere(traceRadius)};
	const FCollisionQueryParams ignoreParams{
			FName{TEXT("Ignore Collision Parameters")},
			true,
			ownerCharacter
		};

	const bool hasFoundTarget{
			GetWorld()->SweepSingleByChannel(
				outResult,
				currentLocation,
				currentLocation,
				FQuat::Identity,
				ECollisionChannel::ECC_GameTraceChannel1,
				sphereCollisionShape,
				ignoreParams
			)
		};

	if (!hasFoundTarget) { return; }

	UE_LOG(LogTemp, Warning, TEXT("LockOn : Has found Target %s"), *outResult.GetActor()->GetName());

	AActor* targetActor = outResult.GetActor();

	if (!targetActor->Implements<ULockOnable>()) { return; }

	lockOnTarget(targetActor);
}

void ULockOnComponent::lockOnTarget(AActor* targetActor) {
	if (!IsValid(targetActor)) { return; }

	currentTargetActor = targetActor;
	playerController->SetIgnoreLookInput(true);
	characterMovementComponent->bOrientRotationToMovement = false;
	characterMovementComponent->bUseControllerDesiredRotation = true;

	originalCameraTargetOffSet = springArmComponent->TargetOffset;
	springArmComponent->TargetOffset = cameraTargetOffSet;

	UE_LOG(LogTemp, Warning, TEXT("Calling LockOn Interface: Has found Target %s"), *targetActor->GetName());
	ILockOnable::Execute_onLockOn(targetActor);

	OnUpdatedTargetDelegate.Broadcast(targetActor);
}

void ULockOnComponent::removeLockOn() {
	ILockOnable::Execute_onRemoveLockOn(currentTargetActor);
	currentTargetActor = nullptr;

	playerController->ResetIgnoreLookInput();
	characterMovementComponent->bOrientRotationToMovement = true;
	characterMovementComponent->bUseControllerDesiredRotation = false;

	springArmComponent->TargetOffset = originalCameraTargetOffSet;

	OnUpdatedTargetDelegate.Broadcast(currentTargetActor);
}

void ULockOnComponent::endLockOn() {
	UE_LOG(LogTemp, Warning, TEXT("EndLockOn : "));

	removeLockOn();
}


void ULockOnComponent::lookAtCurrentTarget(FVector& targetLocation, const FVector currentLocation) const {
	targetLocation.Z -= lookAtTargetZOffSet;

	const FRotator rotation{UKismetMathLibrary::FindLookAtRotation(currentLocation, targetLocation)};

	playerController->SetControlRotation(rotation);
}

bool ULockOnComponent::outsideBreakDistance(FVector targetLocation, const FVector currentLocation) const {
	double currentDistance = {FVector::Distance(targetLocation, currentLocation)};
	return currentDistance >= lockOnBreakDistance;
}

// Called every frame
void ULockOnComponent::TickComponent(float DeltaTime, ELevelTick TickType,
                                     FActorComponentTickFunction* ThisTickFunction) {
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (!IsValid(currentTargetActor)) { return; }

	FVector targetLocation{currentTargetActor->GetActorLocation()};
	const FVector currentLocation{ownerCharacter->GetActorLocation()};

	if (outsideBreakDistance(targetLocation, currentLocation)) {
		endLockOn();
		return;
	}

	lookAtCurrentTarget(targetLocation, currentLocation);
}
