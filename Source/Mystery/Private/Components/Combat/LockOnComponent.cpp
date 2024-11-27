// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/Combat/LockOnComponent.h"
#include "GameFramework/Character.h"
#include "GameFramework/CharacterMovementComponent.h"

// Sets default values for this component's properties
ULockOnComponent::ULockOnComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void ULockOnComponent::BeginPlay()
{
	Super::BeginPlay();

	ownerCharacter = GetOwner<ACharacter>();

	playerController = GetWorld()->GetFirstPlayerController();

	characterMovementComponent = ownerCharacter->GetCharacterMovement();	
}

void ULockOnComponent::startLockOn(float traceRadius) {
	UE_LOG(LogTemp, Warning, TEXT("LockOn Started"));

	FHitResult outResult;
	FVector currentLocation{ ownerCharacter->GetActorLocation() };

	FCollisionShape sphereCollisionShape{ FCollisionShape::MakeSphere(traceRadius) };
	FCollisionQueryParams ignoreParams{
		FName { TEXT("Ignore Collision Parameters")},
		true,
		ownerCharacter
	};


	bool hasFoundTarget{ GetWorld()->SweepSingleByChannel(
		outResult,
		currentLocation,
		currentLocation,
		FQuat::Identity,
		ECollisionChannel::ECC_GameTraceChannel1,
		sphereCollisionShape,
		ignoreParams
	) };

	if (!hasFoundTarget) { return; }

	UE_LOG(LogTemp, Warning, TEXT("LockOn : Has found Target %s"), *outResult.GetActor()->GetName());

	playerController->SetIgnoreLookInput(true);
	characterMovementComponent->bOrientRotationToMovement = false;
	characterMovementComponent->bUseControllerDesiredRotation = true;

}


// Called every frame
void ULockOnComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

