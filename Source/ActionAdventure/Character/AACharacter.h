#pragma once

#include "AbilitySystemInterface.h"
#include "GameFramework/Character.h"
#include "AACharacter.generated.h"

class UAAGameplayAttributeSerializerComponent;
class UAAPersistentModelEntityComponent;
struct FGameplayEffectModCallbackData;
class UAAAbilitySystem;

UCLASS()
class AAACharacter : public ACharacter, public IAbilitySystemInterface
{
	GENERATED_BODY()

public:
	AAACharacter();

	virtual  void PreInitializeComponents() override;
	
	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;

	void PersistentModelSpawn(struct FAAPMStateActor& PMActor);
	
protected:

	void OnMovementSpeedAttributeChanged(float NewValue, const struct FGameplayEffectModCallbackData* CallbackData);

	
protected:
	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UAAAbilitySystem> AbilitySystemComponent;

	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UAAPersistentModelEntityComponent> EntityComponent;
	
	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UAAGameplayAttributeSerializerComponent> GameplayAttributeSerializerComponent;
	
};
