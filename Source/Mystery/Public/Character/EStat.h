// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

UENUM(BlueprintType)
enum EStat {
	None UMETA(DisplayName = "None"),
	Health UMETA(DisplayName = "Health"),
	MaxHealth UMETA(DisplayName = "MaxHealth"),
	Strength UMETA(DisplayName = "Strength"),
	Stamina UMETA(DisplayName = "Stamina"),
	MaxStamina UMETA(DisplayName = "MaxStamina"),
	MeleeRange UMETA(DisplayName = "MeleeRange")
};