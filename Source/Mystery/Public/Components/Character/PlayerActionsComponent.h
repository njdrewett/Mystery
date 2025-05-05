// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Player/MainPlayer.h"
#include "PlayerActionsComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_SPARSE_DELEGATE_OneParam(
	FOnSprintSignature,
	UPlayerActionsComponent,
	OnSprintDelegate,
	float, cost);

DECLARE_DYNAMIC_MULTICAST_SPARSE_DELEGATE_OneParam(
	FOnRollSignature,
	UPlayerActionsComponent,
	OnRollDelegate,
	float, cost);


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class MYSTERY_API UPlayerActionsComponent : public UActorComponent
{
	GENERATED_BODY()

	ACharacter* Character;

	class UCharacterMovementComponent* MovementComponent;

	IMainPlayer* IMainPlayer;

	UPROPERTY(EditAnywhere)
	float sprintSpeed {750.0f};

	UPROPERTY(EditAnywhere)
	float sprintCost {0.5f};

	UPROPERTY(EditAnywhere)
	float walkSpeed {500.0f};

	UPROPERTY(EditAnywhere)
	float rollCost {5.0f};
	
	UPROPERTY(EditAnywhere)
	UAnimMontage* rollAnimMotange;
	
public:	
	// Sets default values for this component's properties
	UPlayerActionsComponent();

	UPROPERTY(BlueprintAssignable)
	FOnSprintSignature OnSprintDelegate;

	UPROPERTY(BlueprintAssignable)
	FOnRollSignature OnRollDelegate;

	bool isRollActive {false};

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UFUNCTION(BlueprintCallable)
	void sprint();

	UFUNCTION(BlueprintCallable)
	void walk();

	UFUNCTION(BlueprintCallable)
	void roll();

	UFUNCTION()
	void RollAnimationFinished();
};
