#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemComponent.h"

#include "AAAbilitySystem.generated.h"


UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class ACTIONADVENTURE_API UAAAbilitySystem : public UAbilitySystemComponent
{
	GENERATED_BODY()

public:
	virtual void InitializeComponent() override;
	
public:
	UPROPERTY(EditAnywhere)
	TArray <TSubclassOf<UGameplayEffect>> DefaultEffects;
	
	UPROPERTY(EditAnywhere)
	TArray<TSubclassOf<UAttributeSet>> DefaultAttributes;
	
	
};
