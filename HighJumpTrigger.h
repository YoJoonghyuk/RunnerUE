#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "HighJumpTrigger.generated.h"

class UBoxComponent; // Предварительное объявление компонента коробки
class AMyProject22Character; // Предварительное объявление вашего класса персонажа

UCLASS()
class MYPROJECT22_API AHighJumpTrigger : public AActor
{
    GENERATED_BODY()

public:
    AHighJumpTrigger();

protected:
    virtual void BeginPlay() override;

public:
    virtual void Tick(float DeltaTime) override;

    UPROPERTY(VisibleAnywhere)
        UBoxComponent* TriggerBox;

    UPROPERTY(VisibleAnywhere)
        class UStaticMeshComponent* MeshComponent;

    UFUNCTION()
        void OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
            UPrimitiveComponent* OtherComp, int32 OtherBodyIndex,
            bool bFromSweep, const FHitResult& SweepResult);

    
protected:
    AMyProject22Character* PlayerCharacter;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Jump")
        float JumpIncreaseValue = 900.0f; 

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Jump")
        float JumpDuration = 5.0f; 
};
