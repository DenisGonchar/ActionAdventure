#include "AACharacter.h"
#include "ActionAdventure/AbilitySystem/AAAbilitySystem.h"
#include "ActionAdventure/AbilitySystem/Attributes/AADamageAttributeSet.h"
#include "ActionAdventure/AbilitySystem/Attributes/AAHealthAttributeSet.h"
#include "ActionAdventure/AbilitySystem/Attributes/AAMovementAttributeSet.h"
#include "ActionAdventure/PersistentModel/AAPersistentModelEntityComponent.h"
#include "ActionAdventure/PersistentModel/AAPersistentModelState.h"
#include "Components/AAGameplayAttributeSerializerComponent.h"
#include "GameFramework/CharacterMovementComponent.h"

AAACharacter::AAACharacter()
{
	AbilitySystemComponent = CreateDefaultSubobject<UAAAbilitySystem>(TEXT("AbilitySystemComponent"));

	EntityComponent = CreateDefaultSubobject<UAAPersistentModelEntityComponent>(TEXT("EntityComponent"));

	GameplayAttributeSerializerComponent = CreateDefaultSubobject<UAAGameplayAttributeSerializerComponent>(
		TEXT("GameplayAttrivuteSerializerComponent"));
}

void AAACharacter::PreInitializeComponents()
{
	Super::PreInitializeComponents();

	AbilitySystemComponent->AddSet<UAAHealthAttributeSet>();
	AbilitySystemComponent->AddSet<UAAMovementAttributeSet>();
	AbilitySystemComponent->AddSet<UAADamageAttributeSet>();

	AbilitySystemComponent->RegisterGameplayAttributeEvent(UAAMovementAttributeSet::GetMovementSpeedAttribute()).AddUObject(this,
		&AAACharacter::OnMovementSpeedAttributeChanged);
}

UAbilitySystemComponent* AAACharacter::GetAbilitySystemComponent() const
{
	return AbilitySystemComponent;
	
}

void AAACharacter::PersistentModelSpawn(FAAPMStateActor& PMActor)
{
	PMActor.Id = EntityComponent->Id;
}

void AAACharacter::OnMovementSpeedAttributeChanged(float NewValue, const struct FGameplayEffectModCallbackData* CallbackData)
{
	GetCharacterMovement()->MaxWalkSpeed = NewValue;
	
}
