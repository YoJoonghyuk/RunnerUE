#include "MyTrigger.h"
#include "Kismet/GameplayStatics.h"
#include "Components/BoxComponent.h"
#include "MyProject22Character.h"

AMyTrigger::AMyTrigger()
{
    TriggerBox = CreateDefaultSubobject<UBoxComponent>(TEXT("TriggerBox"));
    RootComponent = TriggerBox;

    TriggerBox->InitBoxExtent(FVector(50.0f, 50.0f, 50.0f));
    TriggerBox->OnComponentBeginOverlap.AddDynamic(this, &AMyTrigger::OnOverlapBegin);

    SpikeMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("SpikeMesh"));
    SpikeMesh->SetupAttachment(RootComponent); 

    SpikeMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);
    SpikeMesh->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Ignore);
}

void AMyTrigger::BeginPlay()
{
    Super::BeginPlay();
}

void AMyTrigger::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
}

void AMyTrigger::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
    UPrimitiveComponent* OtherComp, int32 OtherBodyIndex,
    bool bFromSweep, const FHitResult& SweepResult)
{
    if (OtherActor && (OtherActor != this))
    {
        AMyProject22Character* PlayerCharacter = Cast<AMyProject22Character>(OtherActor);
        if (PlayerCharacter)
        {
            if (!PlayerCharacter->bHasShield)
            {
                UGameplayStatics::OpenLevel(this, FName(*GetWorld()->GetName()), false);
            }
            else
            {
                UE_LOG(LogTemp, Warning, TEXT("»грок с щитом, шипы не могут его тронуть!"));
                PlayerCharacter->bHasShield = false;
                Destroy();
            }
        }
    }
}

