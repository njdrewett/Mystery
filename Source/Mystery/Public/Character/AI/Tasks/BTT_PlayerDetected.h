// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "BTT_PlayerDetected.generated.h"

/**
 * 
 */
UCLASS()
class MYSTERY_API UBTT_PlayerDetected : public UBTTaskNode
{
	GENERATED_BODY()

	ACharacter* CharacterRef;

	UPROPERTY(EditAnywhere)
	double threshold {0.9};

public:	
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& Comp, uint8* NodeMemory) override;
};
