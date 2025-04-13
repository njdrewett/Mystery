// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "FTraceSockets.generated.h"
/**
 * 
 */
USTRUCT(BlueprintType)
struct MYSTERY_API FTraceSockets
{
	GENERATED_BODY();
	
	UPROPERTY(EditAnywhere)
	FName startSocketName;
	
	UPROPERTY(EditAnywhere)
	FName endSocketName;
	
	UPROPERTY(EditAnywhere)
	FName rotationSocketName;

	UPROPERTY(EditAnywhere)
	double boxCollisionLength {30.0};
	
	UPROPERTY(EditAnywhere)
	bool debugMode {false};
};
