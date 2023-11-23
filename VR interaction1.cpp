#include "YourVRCharacter.h"
#include "MotionControllerComponent.h"
#include "GameFramework/Actor.h"
#include "GameFramework/PlayerController.h"
#include "Engine/World.h"
#include "DrawDebugHelpers.h"

VRCharacter::VRCharacter()
{
    PrimaryActorTick.bCanEverTick = true;
    LeftMotionController = CreateDefaultSubobject<UMotionControllerComponent>(TEXT("LeftMotionController"));
    LeftMotionController->SetupAttachment(GetRootComponent());

    RightMotionController = CreateDefaultSubobject<UMotionControllerComponent>(TEXT("RightMotionController"));
    RightMotionController->SetupAttachment(GetRootComponent());
    TraceDistance = 200.0f;
    GrabbedObject = nullptr;
}


void VRCharacter::BeginPlay()
{
    Super::BeginPlay();
}


void VRCharacter::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

    FHitResult HitResult;
    FVector TraceStart = LeftMotionController->GetComponentLocation();
    FVector TraceEnd = TraceStart + LeftMotionController->GetForwardVector() * TraceDistance;

    if (TraceForGrabbable(HitResult, TraceStart, TraceEnd))
    {

        DrawDebugLine(GetWorld(), TraceStart, HitResult.Location, FColor::Green);
    }
}

void AYourVRCharacter::Grab()
{
    if (!GrabbedObject)
    {

        FHitResult HitResult;
        FVector TraceStart = LeftMotionController->GetComponentLocation();
        FVector TraceEnd = TraceStart + LeftMotionController->GetForwardVector() * TraceDistance;
        if (TraceForGrabbable(HitResult, TraceStart, TraceEnd))
        {
            AActor* HitActor = HitResult.GetActor();
            if (HitActor && HitActor->IsA(AStaticMeshActor::StaticClass()))
            {
                GrabbedObject = HitActor;
                GrabbedObject->AttachToComponent(LeftMotionController, FAttachmentTransformRules::SnapToTargetIncludingScale);
            }
        }
    }
}
void AYourVRCharacter::Release()
{
    if (GrabbedObject)
    {
        GrabbedObject->DetachFromActor(FDetachmentTransformRules::KeepWorldTransform);
        GrabbedObject = nullptr;
    }
}

bool AYourVRCharacter::TraceForGrabbable(FHitResult& HitResult, FVector& TraceStart, FVector& TraceEnd)
{
    FCollisionQueryParams CollisionParams;
    CollisionParams.AddIgnoredActor(this);
    return GetWorld()->LineTraceSingleByChannel(HitResult, TraceStart, TraceEnd, ECC_Visibility, CollisionParams);
}

