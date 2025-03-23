// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Fighter.h"
#include "GameCharacter.h"
#include "LockOnable.h"
#include "NPCharacter.generated.h"

UCLASS()
class MYSTERY_API ANPCharacter : public AGameCharacter, public ILockOnable {
	GENERATED_BODY()

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


};
