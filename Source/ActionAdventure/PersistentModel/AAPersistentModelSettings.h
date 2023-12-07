#pragma once

#include "Engine/DeveloperSettings.h"
#include "AAPersistentModelSettings.generated.h"

class UWorld;

UCLASS(Config = Game)
class UAAPersistentModelSettings : public UDeveloperSettings
{
	GENERATED_BODY()

public:

	static const UAAPersistentModelSettings* Get()
	{
		return GetDefault<UAAPersistentModelSettings>();
	};
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Config)
	TSoftObjectPtr<UWorld> DefaultGameMap;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Config)
	bool bAutoSaveEnabled = true;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Config)
	float AutoSaveTime = 1.f;
		
};
