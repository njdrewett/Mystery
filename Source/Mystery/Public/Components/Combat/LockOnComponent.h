// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "LockOnComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_SPARSE_DELEGATE_OneParam(
	FOnUpdatedTargetSignature,
	ULockOnComponent, OnUpdatedTargetDelegate,
	AActor*, newTargetActorRef
);

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class MYSTERY_API ULockOnComponent : public UActorComponent {
	GENERATED_BODY()

	ACharacter* ownerCharacter;

	APlayerController* playerController;

	class UCharacterMovementComponent* characterMovementComponent;

	AActor* currentTargetActor;

	class USpringArmComponent* springArmComponent;

public:
	// Sets default values for this component's properties
	ULockOnComponent();

	UPROPERTY(BlueprintAssignable, Category="Components")
	FOnUpdatedTargetSignature OnUpdatedTargetDelegate;

	AActor* GetCurrentActorTarget() const { return currentTargetActor; };

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	UFUNCTION(BlueprintCallable)
	void toggleLockOn(float traceRadius = 750.0f);

	UFUNCTION(BlueprintCallable)
	void startLockOn(float traceRadius = 750.0f);

	void lookAtCurrentTarget(FVector& targetLocation, FVector currentLocation) const;

	bool outsideBreakDistance(FVector targetLocation, FVector currentLocation) const;

	UPROPERTY(EditAnywhere)
	FVector cameraTargetOffSet{0.0, 0.0, 100.0};

	UPROPERTY(EditAnywhere)
	float lookAtTargetZOffSet{125.0f};

	UPROPERTY(EditAnywhere)
	float lockOnBreakDistance{1000.0f};

private:
	FVector originalCameraTargetOffSet;

	void lockOnTarget(AActor* targetActor);
	void removeLockOn();

public:
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType,
	                           FActorComponentTickFunction* ThisTickFunction) override;

	UFUNCTION(BlueprintCallable)
	void endLockOn();
};
