// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "CombatComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class MYSTERY_API UCombatComponent : public UActorComponent
{
	GENERATED_BODY()
	UPROPERTY(EditAnyWhere)
	TArray <UAnimMontage*> attackMontages;

	ACharacter* characterReference;

	UPROPERTY(VisibleAnywhere)
	int comboCounter {0};

	UPROPERTY(VisibleAnywhere)
	bool canAttack {true};
	

public:	
	// Sets default values for this component's properties
	UCombatComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UFUNCTION(BlueprintCallable)
	void attack();

	UFUNCTION(BlueprintCallable)
	void resetAttack();
	
};
