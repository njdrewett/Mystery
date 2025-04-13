// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/AI/Tasks/BTT_Charge.h"
#include "AIController.h"
#include "Character/Animation/NPCAnimInstance.h"
#include "GameFramework/Character.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Character/AI/ENPCState.h"
#include "Navigation/PathFollowingComponent.h"

void UBTT_Charge::ChargeAtPlayer() {
	UE_LOG(LogTemp, Warning, TEXT("ChargeAtPlayer called"));

	APawn* playerPawn {GetWorld()->GetFirstPlayerController()->GetPawn()};

	FVector playerLocation { playerPawn->GetActorLocation()};

	FAIMoveRequest moveRequest {playerLocation};
	moveRequest.SetUsePathfinding(true);
	moveRequest.SetAcceptanceRadius(acceptanceRadius);

	aiController->MoveTo(moveRequest);

	aiController->ReceiveMoveCompleted.AddUnique(MoveCompletedDelegate);
}

void UBTT_Charge::HandleMoveCompleted() {

	npcAnimInstance->isCharging = false;
	FTimerHandle timerHandle;
	character->GetWorldTimerManager().SetTimer(timerHandle,this,
		&UBTT_Charge::FinishChargeTask,1.0f,false);
}

void UBTT_Charge::FinishChargeTask() {
	UE_LOG(LogTemp, Warning, TEXT("FinishChargeTask called"));

	isFinished = true;
}

void UBTT_Charge::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) {
	Super::TickTask(OwnerComp, NodeMemory, DeltaSeconds);
	bool isReadyToCharge = OwnerComp.GetBlackboardComponent()->GetValueAsBool("isReadyToCharge");
	if (isReadyToCharge) {
		OwnerComp.GetBlackboardComponent()->SetValueAsBool("isReadyToCharge", false);

		ChargeAtPlayer();
	}

	if (!isFinished) { return; }

	OwnerComp.GetBlackboardComponent()->SetValueAsEnum("CurrentState", ENPCState::Melee);
	
	aiController->ReceiveMoveCompleted.Remove(MoveCompletedDelegate);
	
	FinishLatentTask(OwnerComp,EBTNodeResult::Succeeded);
}

UBTT_Charge::UBTT_Charge() {
	bNotifyTick = true;

	MoveCompletedDelegate.BindUFunction(this, FName("HandleMoveCompleted"));
}

EBTNodeResult::Type UBTT_Charge::ExecuteTask(UBehaviorTreeComponent& Comp, uint8* NodeMemory) {

	aiController = Comp.GetAIOwner();

	character = aiController->GetCharacter();

	npcAnimInstance = Cast<UNPCAnimInstance>(character->GetMesh()->GetAnimInstance());

	npcAnimInstance->isCharging = true;

	Comp.GetBlackboardComponent()->SetValueAsBool("isReadyToCharge",true);

	isFinished = false;
	
	return EBTNodeResult::InProgress;
}
