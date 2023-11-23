

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "YourVRCharacter.generated.h"

UCLASS()
class YOURPROJECT_API AYourVRCharacter : public ACharacter
{
    GENERATED_BODY()

public:
    AYourVRCharacter();

protected:
    virtual void BeginPlay() override;

public:
    virtual void Tick(float DeltaTime) override;
    UFUNCTION(BlueprintCallable, Category = "VRInteraction")
    void Grab();
    UFUNCTION(BlueprintCallable, Category = "VRInteraction")
    void Release();

private:
    UPROPERTY(VisibleAnywhere)
    class UMotionControllerComponent* LeftMotionController;
    UPROPERTY(VisibleAnywhere)
    class UMotionControllerComponent* RightMotionController;
    AActor* GrabbedObject;
    UPROPERTY(EditAnywhere)
    float TraceDistance;

    bool TraceForGrabbable(FHitResult& HitResult, FVector& TraceStart, FVector& TraceEnd);
};
