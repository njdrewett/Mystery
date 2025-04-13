// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/AI/Service/BTS_PlayerDistance.h"

#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"

void UBTS_PlayerDistance::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) {
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);

	FVector currentLocation {OwnerComp.GetAIOwner()->GetPawn()->GetActorLocation()};

	FVector playerLocation {GetWorld()->GetFirstPlayerController()->GetPawn()->GetActorLocation()};

	float distance {static_cast<float>(FVector::Distance(currentLocation, playerLocation))};

	OwnerComp.GetBlackboardComponent()->SetValueAsFloat("DistanceToPlayer", distance);
	UE_LOG(LogTemp, Warning, TEXT("Distance: %f"), distance);
		
}
