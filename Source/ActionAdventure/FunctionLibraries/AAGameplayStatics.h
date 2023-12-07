#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"

#include "AAGameplayStatics.generated.h"


class AAAPlayerCharacter;

UCLASS()
class ACTIONADVENTURE_API UAAGameplayStatics : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintPure,  meta = (WorldContext = "WorldContext"))
	static AAAPlayerCharacter* GetPlayerCharacter(const UObject* WorldContext);

	
};
