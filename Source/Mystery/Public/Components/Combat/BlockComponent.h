// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "BlockComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_SPARSE_DELEGATE_OneParam(
	FOnBlockSigniture,
	UBlockComponent, OnBlockDelegate,
	float , cost
	);


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class MYSTERY_API UBlockComponent : public UActorComponent
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere)
	float StaminaCost {10.0f};

	UPROPERTY(EditAnywhere)
	UAnimMontage* blockAnimMontage;
public:	
	// Sets default values for this component's properties
	UBlockComponent();

	UPROPERTY(BlueprintAssignable)
	FOnBlockSigniture OnBlockDelegate;
	
protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	bool Check(AActor* attacker);;
};
