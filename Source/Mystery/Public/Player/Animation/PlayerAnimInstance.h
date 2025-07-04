// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "PlayerAnimInstance.generated.h"

/**
 * 
 */
UCLASS()
class MYSTERY_API UPlayerAnimInstance : public UAnimInstance {
	GENERATED_BODY()

protected:
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	bool isLockOnMovement{false};

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	float currentDirection{0.0f};

	UFUNCTION(BlueprintCallable)
	void updateLockOnTarget(AActor* lockonTarget);

	UFUNCTION(BlueprintCallable)
	void updateDirection();

public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	bool isBlocking{false};
};
