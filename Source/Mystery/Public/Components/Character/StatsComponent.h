// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Character/EStat.h"
#include "Components/ActorComponent.h"
#include "StatsComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_SPARSE_DELEGATE_OneParam(
	FOnHealthPercentageUpdateSignature,
	UStatsComponent, OnHealthPercentageUpdateDelegate,
	float, Percentage
);

DECLARE_DYNAMIC_MULTICAST_SPARSE_DELEGATE_OneParam(
	FOnStaminaPercentageUpdateSignature,
	UStatsComponent, OnStaminaPercentageUpdateDelegate,
	float, Percentage
);

DECLARE_DYNAMIC_MULTICAST_SPARSE_DELEGATE(
	FOnHealthZeroSignature,
	UStatsComponent, onHealthZeroDelegate
);

UCLASS( ClassGroup=(Custom),Blueprintable, BlueprintType, meta=(BlueprintSpawnableComponent) )
class MYSTERY_API UStatsComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UStatsComponent();

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TMap<TEnumAsByte<EStat>, float> Stats;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float staminaRegenerationRate { 10.0f };

	UPROPERTY(VisibleAnywhere)
	bool canRegenerateStamina {true};

	UPROPERTY(EditAnywhere)
	float staminaRegenerationDelay {2.0f};

	UPROPERTY(BlueprintAssignable)
	FOnHealthZeroSignature onHealthZeroDelegate;

	UPROPERTY(BlueprintAssignable)
	FOnHealthPercentageUpdateSignature OnHealthPercentageUpdateDelegate;
	
	UPROPERTY(BlueprintAssignable)
	FOnStaminaPercentageUpdateSignature OnStaminaPercentageUpdateDelegate;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UFUNCTION(BlueprintCallable)
	void ReduceHealth(float Amount, AActor* attacker);
	
	void ReduceStatByValue(float Amount, EStat stat, EStat maxStat);

	UFUNCTION(BlueprintCallable)
	void ReduceStamina(float Amount);	

	UFUNCTION( BlueprintCallable)
	void RegenerateStamina();

	UFUNCTION( )
	void enableRegenerateStamina();

	UFUNCTION( BlueprintPure )
	float GetStatPercentage(EStat Current, EStat Maximum);
};
