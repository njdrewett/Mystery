// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/AI/Tasks/BTT_MeleeAttack.h"

#include "AIController.h"
#include "Character/AI/ENPCState.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Character/Fighter.h"
#include "GameFramework/Character.h"
#include "Navigation/PathFollowingComponent.h"

EBTNodeResult::Type UBTT_MeleeAttack::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) {

	isFinished = false;
	
	float distance {
		OwnerComp.GetBlackboardComponent()->GetValueAsFloat("DistanceToPlayer")
	};
	
	AAIController* AIController {OwnerComp.GetAIOwner()};
	
	if (distance > attackRadius) {
		APawn* playerRef {GetWorld()->GetFirstPlayerController()->GetPawn()};
		FAIMoveRequest moveRequest { playerRef };
		moveRequest.SetUsePathfinding(true);
		moveRequest.SetAcceptanceRadius(acceptableRadius);

		AIController->ReceiveMoveCompleted.AddUnique(moveDelegate);

		AIController->MoveTo(moveRequest);
		AIController->SetFocus(playerRef);
	} else {
		IFighter* fighter {
			Cast<IFighter>(AIController->GetCharacter())
		};

		fighter->attack();

		FTimerHandle timerHandle;
		AIController->GetCharacter()->GetWorldTimerManager().SetTimer(
			timerHandle, this,
			&UBTT_MeleeAttack::FinishAttackTask, fighter->GetAnimationDuration(), false);
	}
	
	return EBTNodeResult::InProgress;
}

void UBTT_MeleeAttack::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) {
	Super::TickTask(OwnerComp, NodeMemory, DeltaSeconds);

	float Distance {OwnerComp.GetBlackboardComponent()->GetValueAsFloat("DistanceToPlayer")};

	AAIController* AIController {OwnerComp.GetAIOwner()};
	
	IFighter* fighter {
		Cast<IFighter>(AIController->GetCharacter())
	};

	if (Distance > fighter->GetMeleeRange()) {
		OwnerComp.GetBlackboardComponent()->SetValueAsEnum("CurrentState", ENPCState::PlayerDetected);
		AbortTask(OwnerComp, NodeMemory);
		FinishLatentTask(OwnerComp, EBTNodeResult::Aborted);

		AIController->StopMovement();
		AIController->ClearFocus(EAIFocusPriority::Gameplay);

		AIController->ReceiveMoveCompleted.Remove(moveDelegate);
	}
	
	if (!isFinished) {		return;	}

	OwnerComp.GetAIOwner()->ReceiveMoveCompleted.Remove(moveDelegate);
	
	FinishLatentTask(OwnerComp,EBTNodeResult::Succeeded);
}

UBTT_MeleeAttack::UBTT_MeleeAttack() {
	bNotifyTick = true;
	bCreateNodeInstance = true;
	moveDelegate.BindUFunction(this, FName("FinishAttackTask"));
}

void UBTT_MeleeAttack::FinishAttackTask() {
	isFinished = true;
}
