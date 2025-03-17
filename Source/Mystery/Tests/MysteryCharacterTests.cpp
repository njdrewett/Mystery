#include "InputActionValue.h"
#include "Misc/AutomationTest.h"
#include "../MysteryCharacter.h"
#include "Engine/World.h"
#include "GameFramework/PawnMovementComponent.h"
#include "GameFramework/PlayerController.h"
#include "Tests/AutomationEditorCommon.h"

// Subclass to expose protected methods
class TestableMysteryCharacter : public AMysteryCharacter
{
public:
    using AMysteryCharacter::Move;
    using AMysteryCharacter::Look;
};

IMPLEMENT_SIMPLE_AUTOMATION_TEST(FMysteryCharacterMoveTest, "MysteryCharacter.Move", EAutomationTestFlags::EditorContext | EAutomationTestFlags::EngineFilter)

bool FMysteryCharacterMoveTest::RunTest(const FString& Parameters)
{
    // Create a test world
    UWorld* World = FAutomationEditorCommonUtils::CreateNewMap();
    if (!World) return false;

    // Spawn a TestableMysteryCharacter
    TestableMysteryCharacter* Character = World->SpawnActor<TestableMysteryCharacter>();
    if (!Character) return false;

    // Create a mock controller
    APlayerController* Controller = World->SpawnActor<APlayerController>();
    if (!Controller) return false;
    Controller->Possess(Character);

    Character->GetMovementComponent()->SetUpdatedComponent(Character->GetRootComponent());

    // Test moving forward
    FInputActionValue MoveValue(FVector2D(1.0f, 0.0f));
    Character->Move(MoveValue);
    TestTrue("Character should move forward", Character->GetPendingMovementInputVector().Y > 0);

    // Test moving right
    MoveValue = FInputActionValue(FVector2D(0.0f, 1.0f));
    Character->Move(MoveValue);
    TestTrue("Character should move right", Character->GetPendingMovementInputVector().X > 0);

    // Test no movement
    MoveValue = FInputActionValue(FVector2D(0.0f, 0.0f));
    Character->Move(MoveValue);
    TestTrue("Character should not move", Character->GetPendingMovementInputVector().X == 1);

    return true;
}

IMPLEMENT_SIMPLE_AUTOMATION_TEST(FMysteryCharacterLookTest, "MysteryCharacter.Look", EAutomationTestFlags::EditorContext | EAutomationTestFlags::EngineFilter)

bool FMysteryCharacterLookTest::RunTest(const FString& Parameters)
{
    // Create a test world
    UWorld* World = FAutomationEditorCommonUtils::CreateNewMap();
    if (!World) return false;

    // Spawn a TestableMysteryCharacter
    TestableMysteryCharacter* Character = World->SpawnActor<TestableMysteryCharacter>();
    if (!Character) return false;

    // Create a mock controller
    APlayerController* Controller = World->SpawnActor<APlayerController>();
    if (!Controller) return false;
    Character->PossessedBy(Controller);

    // Test looking around
    FInputActionValue LookValue(FVector2D(1.0f, 1.0f));
    Character->Look(LookValue);
    TestTrue("Character should look around", Controller->RotationInput.Yaw != 0 || Controller->RotationInput.Pitch != 0);

    FRotator rotation1 = Controller->GetControlRotation();
    // Test no look
    LookValue = FInputActionValue(FVector2D(0.0f, 0.0f));
    Character->Look(LookValue);
    TestTrue("Character should not look around", Controller->GetControlRotation().Yaw == 0 && Controller->GetControlRotation().Pitch == 0);
    FRotator rotation2 = Controller->GetControlRotation();

    return true;
}