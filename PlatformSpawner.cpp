
#include "PlatformSpawner.h"
#include "Kismet/GameplayStatics.h" 

APlatformSpawner::APlatformSpawner()
{
    PrimaryActorTick.bCanEverTick = true;
    LastSpawnLocation = FVector::ZeroVector;
    PreviousDistanceToPlayer = 0.0f;
}

void APlatformSpawner::BeginPlay()
{
    Super::BeginPlay();
    PlayerCharacter = Cast<AMyProject22Character>(UGameplayStatics::GetPlayerPawn(this, 0));
    if (PlayerCharacter)
    {
        InitializePlatformPool();

        for (int32 i = 0; i < 3; i++)
        {
            SpawnPlatform();
        }
    }
}


void APlatformSpawner::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

    if (PlayerCharacter)
    {
        float CurrentDistanceToPlayer = FVector::Dist(PlayerCharacter->GetActorLocation(), LastSpawnLocation);

        if (CurrentDistanceToPlayer < PreviousDistanceToPlayer && CurrentDistanceToPlayer < MinimumDistanceBetweenPlatforms)
        {
            SpawnPlatform();
            RemoveBehindPlatforms();
        }

        PreviousDistanceToPlayer = CurrentDistanceToPlayer;
    }
}

void APlatformSpawner::InitializePlatformPool()
{
    for (int32 i = 0; i < MaxPlatforms; i++)
    {
        int32 RandomIndex = FMath::RandRange(0, PlatformClasses.Num() - 1);
        TSubclassOf<AActor> SelectedPlatformClass = PlatformClasses[RandomIndex];

        AActor* NewPlatform = GetWorld()->SpawnActor<AActor>(SelectedPlatformClass);
        PlatformPool.Add(NewPlatform);

        NewPlatform->SetActorHiddenInGame(true);
    }
}

void APlatformSpawner::SpawnPlatform()
{
    if (PlatformPool.Num() > 0)
    {
        AActor* LastPlatform = ActivePlatforms.Num() > 0 ? ActivePlatforms.Last() : nullptr;

        AActor* PlatformToSpawn = PlatformPool[0];
        PlatformPool.RemoveAt(0);

        FVector SpawnLocation = LastPlatform
            ? LastPlatform->GetActorLocation() + FVector(SpawnDistance, 0, PlatformHeightOffset)
            : PlayerCharacter->GetActorLocation() + FVector(SpawnDistance, 0, PlatformHeightOffset);

        PlatformToSpawn->SetActorLocation(SpawnLocation, true);
        PlatformToSpawn->SetActorHiddenInGame(false);
        ActivePlatforms.Add(PlatformToSpawn);
        LastSpawnLocation = PlatformToSpawn->GetActorLocation();
    }
}


void APlatformSpawner::RemoveBehindPlatforms()
{
    FVector PlayerLocation = PlayerCharacter->GetActorLocation();

    for (int32 i = ActivePlatforms.Num() - 1; i >= 0; i--)
    {
        AActor* Platform = ActivePlatforms[i];

        if (Platform && Platform->GetActorLocation().X < PlayerLocation.X - OffsetBehindPlayer)
        {
            Platform->SetActorHiddenInGame(true);
            ActivePlatforms.RemoveAt(i);
            PlatformPool.Add(Platform);
        }
    }
}

