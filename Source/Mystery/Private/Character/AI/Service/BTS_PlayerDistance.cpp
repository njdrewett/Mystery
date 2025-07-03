// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/AI/Service/BTS_PlayerDistance.h"

#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"


/**
 * Service to check the distance from the player and update the blackboard value.
 * @param OwnerComp 
 * @param NodeMemory 
 * @param DeltaSeconds 
 */
void UBTS_PlayerDistance::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) {
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);

	APawn* Pawn = GetWorld()->GetFirstPlayerController()->GetPawn();
	if (Pawn == nullptr) { return; }

	FVector currentLocation{OwnerComp.GetAIOwner()->GetPawn()->GetActorLocation()};

	FVector playerLocation{Pawn->GetActorLocation()};

	float distance{static_cast<float>(FVector::Distance(currentLocation, playerLocation))};

	OwnerComp.GetBlackboardComponent()->SetValueAsFloat("DistanceToPlayer", distance);
	UE_LOG(LogTemp, Warning, TEXT("Distance: %f"), distance);
}
