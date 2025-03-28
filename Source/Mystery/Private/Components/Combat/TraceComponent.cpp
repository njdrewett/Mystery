// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/Combat/TraceComponent.h"

#include "Kismet/KismetSystemLibrary.h"
#include "Kismet/KismetMathLibrary.h"
#include "Character/Fighter.h"
#include "Engine/DamageEvents.h"

// Sets default values for this component's properties
UTraceComponent::UTraceComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UTraceComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	SkeletalMeshComponent = GetOwner()->FindComponentByClass<USkeletalMeshComponent>();
	
}


// Called every frame
void UTraceComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) {
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (!isAttacking) { return ; }
	// ...
	FVector startSocketLocation { SkeletalMeshComponent->GetSocketLocation(startSocketName)};
	FVector endSocketLocation  { SkeletalMeshComponent->GetSocketLocation(endSocketName)};
	FQuat shapeRotation {SkeletalMeshComponent->GetSocketQuaternion(rotationSocketName)};

	TArray<FHitResult> hitResults;

	double weaponDistance {FVector::Distance(startSocketLocation, endSocketLocation)};

	FVector boxHalfExtent {boxCollisionLength, boxCollisionLength, weaponDistance};
	boxHalfExtent /= 2;

	FCollisionShape sweepBox {FCollisionShape::MakeBox(boxHalfExtent)};

	// Ignore Parameters
	FCollisionQueryParams ignoreParams {
		FName {TEXT("Ignore params")},
false,
		GetOwner()
	};
	
	bool hasFoundTargets { GetWorld()->SweepMultiByChannel(
		hitResults,
		startSocketLocation,
		endSocketLocation,
		shapeRotation,
		ECC_GameTraceChannel1,
		sweepBox,
		ignoreParams
		)};
	
	if (debugMode) {
		FVector centerPoint{
			UKismetMathLibrary::VLerp(startSocketLocation, endSocketLocation, 0.5f)
		};
		
		UKismetSystemLibrary::DrawDebugBox(
			GetWorld(),
			centerPoint,
			sweepBox.GetExtent(),
			hasFoundTargets? FLinearColor::Green : FLinearColor::Red,
			shapeRotation.Rotator(),
			1.0f,2.0f);
		
		// UE_LOG(LogTemp, Display, TEXT("Tick TargetFound Start: %s - End:%s - Rotation: %s"),
		// 	*startSocketLocation.ToString(),*endSocketLocation.ToString(), *shapeRotation.ToString());
	}	

	if (hitResults.Num() == 0) { return;}
	
	float characterDamage{ 0.0f };

	if (IFighter* fighterReference {Cast<IFighter>(GetOwner())}) {
		characterDamage = fighterReference->GetDamage();
	}

	UE_LOG(LogTemp, Warning, TEXT("Damage: %f"), characterDamage);

	for (const FHitResult& Hit: hitResults) {
		FDamageEvent targetAttackedEvent;
		AActor* hitActor {Cast<AActor>(Hit.GetActor())};

		if (targetsToIgnore.Contains(hitActor)) { continue; }
		
		hitActor->TakeDamage(
			characterDamage,
			targetAttackedEvent,
			GetOwner()->GetInstigatorController(),
			GetOwner()
			);

		targetsToIgnore.AddUnique(hitActor);
	}
}

void UTraceComponent::handleResetAttack() {
	targetsToIgnore.Empty();
}

