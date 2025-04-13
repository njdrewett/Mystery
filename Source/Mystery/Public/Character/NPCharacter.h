// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameCharacter.h"
#include "LockOnable.h"
#include "AI/ENPCState.h"
#include "NPCharacter.generated.h"

UCLASS()
class MYSTERY_API ANPCharacter : public AGameCharacter, public ILockOnable {
	GENERATED_BODY()

	UPROPERTY(EditAnywhere)
	TEnumAsByte<ENPCState> InitialState;

	class UBlackboardComponent* BlackboardComponent;

	
public:
	// Sets default values for this character's properties
	ANPCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UFUNCTION(BlueprintCallable)
	bool detectPawn(APawn* detected, APawn* toCheck);
	
	virtual void attack() override;

	virtual float GetAnimationDuration() const override;

	virtual float GetMeleeRange() const override;
};
