#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "MyProject22GameMode.generated.h"

UCLASS()
class MYPROJECT22_API AMyProject22GameMode : public AGameModeBase
{
    GENERATED_BODY()

public:
    AMyProject22GameMode();

protected:
    virtual void BeginPlay() override;

};