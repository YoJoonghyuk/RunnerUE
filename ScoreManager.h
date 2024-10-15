#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Blueprint/UserWidget.h"
#include "Components/TextBlock.h"
#include "ScoreManager.generated.h"

UCLASS()
class MYPROJECT22_API AScoreManager : public AActor
{
    GENERATED_BODY()

public:
    AScoreManager();

protected:
    virtual void BeginPlay() override;

public:
    UFUNCTION(BlueprintCallable, Category = "UI")
        void AddScore(int32 Amount);

    UFUNCTION(BlueprintCallable, Category = "UI")
        void UpdateScoreText();

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UI")
        TSubclassOf<UUserWidget> ScoreWidgetClass;

private:

    UPROPERTY(BlueprintReadOnly, meta = (BindWidget, AllowPrivateAccess = "true"), Category = "UI")
        UTextBlock* ScoreText;

    int32 Score;

    FTimerHandle ScoreTimerHandle; 
    void IncrementScore(); 
};
