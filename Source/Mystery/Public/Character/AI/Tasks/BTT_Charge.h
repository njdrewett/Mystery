// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "BTT_Charge.generated.h"

/**
 * 
 */
UCLASS()
class MYSTERY_API UBTT_Charge : public UBTTaskNode
{
	GENERATED_BODY()

	AAIController* aiController;

	ACharacter* character;

	class UNPCAnimInstance* npcAnimInstance;

	UPROPERTY(EditAnywhere)
	float acceptanceRadius {100.0f};

	void ChargeAtPlayer();

	UFUNCTION()
	void HandleMoveCompleted();

	FScriptDelegate MoveCompletedDelegate;

	UFUNCTION()
	void FinishChargeTask();

	bool isFinished {false};
	
protected:
	virtual void TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;
	
public:
	UBTT_Charge();
	
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& Comp, uint8* NodeMemory) override;
};
