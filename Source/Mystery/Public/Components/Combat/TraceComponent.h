// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "FTraceSockets.h"
#include "Components/ActorComponent.h"
#include "TraceComponent.generated.h"

/**
 * Trace Component is used to trace a weapons collision to detect impacts with other actors.
 */
UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class MYSTERY_API UTraceComponent : public UActorComponent
{
	GENERATED_BODY()

	USkeletalMeshComponent* SkeletalMeshComponent = nullptr;

	UPROPERTY(EditAnywhere)
	TArray<FTraceSockets> TraceSockets;
	
	TArray<AActor*> targetsToIgnore;

	UPROPERTY(EditAnywhere)
	UParticleSystem* hitParticleTemplate;
	
public:	

	// Sets default values for this component's properties
	UTraceComponent();

	UPROPERTY(VisibleAnywhere)
	bool isTracing { false };
	
protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UFUNCTION(BlueprintCallable)
	void handleResetAttack();
};
