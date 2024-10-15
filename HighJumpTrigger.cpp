#include "HighJumpTrigger.h"
#include "Components/BoxComponent.h"
#include "MyProject22Character.h" 
#include "GameFramework/CharacterMovementComponent.h" 
#include "TimerManager.h"

AHighJumpTrigger::AHighJumpTrigger()
{
    TriggerBox = CreateDefaultSubobject<UBoxComponent>(TEXT("TriggerBox"));
    RootComponent = TriggerBox;
    TriggerBox->InitBoxExtent(FVector(50.0f, 50.0f, 50.0f));

    MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComponent"));
    MeshComponent->SetupAttachment(RootComponent);
    MeshComponent->SetCollisionEnabled(ECollisionEnabled::NoCollision);

    TriggerBox->OnComponentBeginOverlap.AddDynamic(this, &AHighJumpTrigger::OnOverlapBegin);
}

void AHighJumpTrigger::BeginPlay()
{
    Super::BeginPlay();
}

void AHighJumpTrigger::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
}

void AHighJumpTrigger::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
    UPrimitiveComponent* OtherComp, int32 OtherBodyIndex,
    bool bFromSweep, const FHitResult& SweepResult)
{
    if (OtherActor && (OtherActor != this))
    {
        TWeakObjectPtr<AMyProject22Character> WeakPlayerCharacter = Cast<AMyProject22Character>(OtherActor);
        if (WeakPlayerCharacter.IsValid())
        {
            WeakPlayerCharacter->GetCharacterMovement()->JumpZVelocity += JumpIncreaseValue;

            FTimerHandle TimerHandle;
            GetWorld()->GetTimerManager().SetTimer(TimerHandle, [WeakPlayerCharacter, this]()
                {
                    if (WeakPlayerCharacter.IsValid())
                    {
                        WeakPlayerCharacter->GetCharacterMovement()->JumpZVelocity -= JumpIncreaseValue;
                    }
                }, JumpDuration, false);
        }
        Destroy(); 
    }
}

