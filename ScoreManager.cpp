#include "ScoreManager.h"
#include "UObject/ConstructorHelpers.h"
#include "Blueprint/UserWidget.h"
#include "TimerManager.h"

AScoreManager::AScoreManager()
{
    Score = 0;
    static ConstructorHelpers::FClassFinder<UUserWidget> WidgetClassFinder(TEXT("WidgetBlueprint'/Game/Geometry/UI/Score_main.Score_main'"));
    if (WidgetClassFinder.Succeeded())
    {
        ScoreWidgetClass = WidgetClassFinder.Class;
    }
}

void AScoreManager::BeginPlay()
{
    Super::BeginPlay();

    if (ScoreWidgetClass)
    {
        UUserWidget* WidgetInstance = CreateWidget<UUserWidget>(GetWorld(), ScoreWidgetClass);
        if (WidgetInstance)
        {
            WidgetInstance->AddToViewport();

            ScoreText = Cast<UTextBlock>(WidgetInstance->GetWidgetFromName(TEXT("ScoreText"))); 
            if (ScoreText)
            {
                UpdateScoreText();
            }
            else
            {
                UE_LOG(LogTemp, Error, TEXT("ScoreText not found! Check the name in Blueprint."));
            }
        }

        GetWorld()->GetTimerManager().SetTimer(ScoreTimerHandle, this, &AScoreManager::IncrementScore, 1.0f, true);
    }
    else
    {
        UE_LOG(LogTemp, Error, TEXT("ScoreWidgetClass not set! Check your settings."));
    }
}

void AScoreManager::IncrementScore()
{
    AddScore(1); 
}

void AScoreManager::UpdateScoreText()
{
    if (ScoreText)
    {
        ScoreText->SetText(FText::FromString(FString::Printf(TEXT("Score: %d"), Score)));
    }
    else
    {
        UE_LOG(LogTemp, Error, TEXT("ScoreText is not set!"));
    }
}

void AScoreManager::AddScore(int32 Amount)
{
    Score += Amount; 
    UpdateScoreText(); 
}
