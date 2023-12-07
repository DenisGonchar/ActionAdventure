#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "AAGameInstance.generated.h"

UCLASS()
class ACTIONADVENTURE_API UAAGameInstance : public UGameInstance
{
	GENERATED_BODY()

public:
	virtual void Init() override;

};
