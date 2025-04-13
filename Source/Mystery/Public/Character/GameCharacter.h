// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Fighter.h"
#include "Components/Character/StatsComponent.h"
#include "Components/Combat/TraceComponent.h"
#include "Components/Combat/CombatComponent.h"
#include "GameFramework/Character.h"
#include "GameCharacter.generated.h"

UCLASS()
class MYSTERY_API AGameCharacter : public ACharacter, public IFighter
{
	GENERATED_BODY()


public:
	// Sets default values for this character's properties
	AGameCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere)
	UAnimMontage* deathAnimation;

	/** Components */
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Components, meta = (AllowPrivateAccess = "true"))
	UStatsComponent* StatsComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Components, meta = (AllowPrivateAccess = "true"))
	UTraceComponent* TraceComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Components, meta = (AllowPrivateAccess = "true"))
	UCombatComponent* CombatComponent;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent( UInputComponent* PlayerInputComponent) override;

	virtual float GetDamage() const override;

	UFUNCTION(BlueprintCallable)
	void handleDeath();

	UFUNCTION()
	void finishedDeathAnimation();

};
