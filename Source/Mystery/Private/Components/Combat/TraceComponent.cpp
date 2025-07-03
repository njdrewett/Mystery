// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/Combat/TraceComponent.h"

#include "Kismet/KismetSystemLibrary.h"
#include "Kismet/KismetMathLibrary.h"
#include "Character/Fighter.h"
#include "Engine/DamageEvents.h"
#include "Kismet/GameplayStatics.h"

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

	if (!isTracing) { return ; }
	// ...

	TArray<FHitResult> allResults;
	for (const FTraceSockets sockets : TraceSockets) {
		FVector startSocketLocation { SkeletalMeshComponent->GetSocketLocation(sockets.startSocketName)};
		FVector endSocketLocation  { SkeletalMeshComponent->GetSocketLocation(sockets.endSocketName)};
		FQuat shapeRotation {SkeletalMeshComponent->GetSocketQuaternion(sockets.rotationSocketName)};

		TArray<FHitResult> hitResults;

		double weaponDistance {FVector::Distance(startSocketLocation, endSocketLocation)};

		FVector boxHalfExtent {sockets.boxCollisionLength, sockets.boxCollisionLength, weaponDistance};
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

		allResults.Append(hitResults);
		
		if (sockets.debugMode) {
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
	}
	if (allResults.Num() == 0) { return;}
	
	float characterDamage{ 0.0f };

	if (IFighter* fighterReference {Cast<IFighter>(GetOwner())}) {
		characterDamage = fighterReference->GetDamage();
	}

	UE_LOG(LogTemp, Warning, TEXT("Damage: %f"), characterDamage);

	for (const FHitResult& Hit: allResults) {
		FDamageEvent targetAttackedEvent;
		AActor* hitActor {Cast<AActor>(Hit.GetActor())};
		
		if (targetsToIgnore.Contains(hitActor)) { UE_LOG(LogTemp, Warning, TEXT("Ignoring Actor")); continue; }
		
		hitActor->TakeDamage(
			characterDamage,
			targetAttackedEvent,
			GetOwner()->GetInstigatorController(),
			GetOwner()
			);

		targetsToIgnore.AddUnique(hitActor);

		UGameplayStatics::SpawnEmitterAtLocation(GetWorld(),
			hitParticleTemplate,
			Hit.ImpactPoint);
	}
}

void UTraceComponent::handleResetAttack() {
	targetsToIgnore.Empty();
}

