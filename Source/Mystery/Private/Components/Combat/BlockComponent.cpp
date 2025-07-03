// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/Combat/BlockComponent.h"
#include "GameFramework/Character.h"
#include "Player/MainPlayer.h"

/**
 *Component to handle blocking actions in combat.
 **/
// Sets default values for this component's properties
UBlockComponent::UBlockComponent(): blockAnimMontage(nullptr) {
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
}


// Called when the game starts
void UBlockComponent::BeginPlay() {
	Super::BeginPlay();
}


// Called every frame
void UBlockComponent::TickComponent(float DeltaTime, ELevelTick TickType,
                                    FActorComponentTickFunction* ThisTickFunction) {
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

bool UBlockComponent::Check(const AActor* attacker) {
	ACharacter* characterRef{GetOwner<ACharacter>()};

	if (!characterRef->Implements<UMainPlayer>()) { return true; }

	IMainPlayer* mainPlayer{Cast<IMainPlayer>(characterRef)};

	FVector attackerForward{attacker->GetActorForwardVector()};
	FVector playerForward{characterRef->GetActorForwardVector()};

	double dotProduct{FVector::DotProduct(attackerForward, playerForward)};
	if (dotProduct > 0.0 || !mainPlayer->HasStamina(StaminaCost)) {
		UE_LOG(LogTemp, Warning, TEXT("Attacker is not facing or not enough stamina"));
		return true;
	}

	characterRef->PlayAnimMontage(blockAnimMontage);

	OnBlockDelegate.Broadcast(StaminaCost);

	return false;
}
