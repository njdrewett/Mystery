// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "BTT_MeleeAttack.generated.h"

/**
 * 
 */
UCLASS()
class MYSTERY_API UBTT_MeleeAttack : public UBTTaskNode
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere)
	float attackRadius {200.0f};

	UPROPERTY(EditAnywhere)
	float acceptableRadius {100.0f};

	FScriptDelegate moveDelegate;

	bool isFinished {false};
	
protected:
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

	virtual void TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;

public:
	UBTT_MeleeAttack();

	UFUNCTION()
	void FinishAttackTask() ;
	
};
