// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Character/ControllableCharacter.h"
#include "PlayerCharacter.generated.h"

class ULockOnComponent;
class UCombatComponent;
class UTraceComponent;

UCLASS()
class MYSTERY_API APlayerCharacter : public AControllableCharacter
{
	GENERATED_BODY()
	
	/** Components */
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Components, meta = (AllowPrivateAccess = "true"))
	ULockOnComponent* LockOnComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Components, meta = (AllowPrivateAccess = "true"))
	UCombatComponent* CombatComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Components, meta = (AllowPrivateAccess = "true"))
	UTraceComponent* TraceComponent;
	
public:
	// Sets default values for this character's properties
	APlayerCharacter();

protected:

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(BlueprintReadOnly)
	class UPlayerAnimInstance* playerAnimInstance;
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
