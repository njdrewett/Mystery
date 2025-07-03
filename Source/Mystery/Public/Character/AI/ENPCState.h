// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

/**
 * 
 */
UENUM(BlueprintType)
enum ENPCState {
	Idle UMETA(DisplayName = "Idle"),
	PlayerDetected UMETA(DisplayName = "PlayerDetected"),
	Charging UMETA(DisplayName = "Charging"),
	Melee UMETA(DisplayName = "Melee"),
	GameOver UMETA(DisplayName = "GameOver")
};
