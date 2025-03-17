// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "TraceComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class MYSTERY_API UTraceComponent : public UActorComponent
{
	GENERATED_BODY()

	USkeletalMeshComponent* SkeletalMeshComponent = nullptr;

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

public:	

	// Sets default values for this component's properties
	UTraceComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;


public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

		
};
