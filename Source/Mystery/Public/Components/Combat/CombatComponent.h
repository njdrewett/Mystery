// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "CombatComponent.generated.h"


DECLARE_DYNAMIC_MULTICAST_SPARSE_DELEGATE_OneParam(
	FOnAttackPerformedSignature,
	UCombatComponent,
	OnAttackPerformedDelegate,
	float, Amount);

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

	UPROPERTY(EditAnywhere)
	float staminaCost {5.0f};

public:	
	// Sets default values for this component's properties
	UCombatComponent();

	UPROPERTY(BlueprintAssignable)
	FOnAttackPerformedSignature OnAttackPerformedDelegate;

	float animationDuration;
	
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

	UFUNCTION(BlueprintCallable)
	void randomAttack();
	
};
