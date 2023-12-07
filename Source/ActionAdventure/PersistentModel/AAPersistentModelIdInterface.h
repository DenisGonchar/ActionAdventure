#pragma once

#include "CoreMinimal.h"
#include "AAPersistentModelTypes.h"
#include "UObject/Interface.h"

#include "AAPersistentModelIdInterface.generated.h"

UINTERFACE(meta=(CannotImplementInterfaceInBlueprint))
class UAAPersistentModelIdInterface : public UInterface
{
	GENERATED_BODY()
};

class IAAPersistentModelIdInterface
{
	GENERATED_BODY()

public:
	virtual const FAAPersistentModelId& GetId() const = 0;
	virtual void SetId(const FAAPersistentModelId& NewId) = 0;
	
};
