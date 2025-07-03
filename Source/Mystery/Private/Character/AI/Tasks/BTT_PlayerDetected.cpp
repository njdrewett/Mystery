// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/AI/Tasks/BTT_PlayerDetected.h"

#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Character/Fighter.h"
#include "Character/AI/ENPCState.h"
#include "GameFramework/Character.h"
#include "Kismet/KismetMathLibrary.h"

class IFighter;

/**
 * AI Task to detect the player and change the state based on the distance.
 * If the player is within melee range, it will set the state to Melee.
 * If the player is out of melee range, it will set the state to Charging.
 */

EBTNodeResult::Type UBTT_PlayerDetected::ExecuteTask(UBehaviorTreeComponent& Comp, uint8* NodeMemory) {
	if (!CharacterRef) {
		CharacterRef = Cast<ACharacter>(Comp.GetAIOwner()->GetPawn());
	}
	if (!IsValid(CharacterRef)) { return EBTNodeResult::Failed; }

	UE_LOG(LogBehaviorTree, Warning, TEXT("BTT_PlayerDetected:Executing task"));

	float distance {Comp.GetBlackboardComponent()->GetValueAsFloat("DistanceToPlayer")};
	IFighter* fighter {
		Cast<IFighter>(CharacterRef)
	};

	if (distance < fighter->GetMeleeRange()) {
		Comp.GetBlackboardComponent()->SetValueAsEnum("CurrentState", Melee);

		AbortTask(Comp, NodeMemory);

		return EBTNodeResult::Aborted;
	}
	
	double randomValue{UKismetMathLibrary::RandomFloat()};

	if (randomValue > threshold) {
		UE_LOG(LogBehaviorTree, Warning, TEXT("BTT_PlayerDetected: Broke threshold"));

		Comp.GetBlackboardComponent()->
		     SetValueAsEnum(TEXT("CurrentState"), Charging);
	} else {
		threshold -= 0.1;
	}

	return EBTNodeResult::Succeeded;
}
