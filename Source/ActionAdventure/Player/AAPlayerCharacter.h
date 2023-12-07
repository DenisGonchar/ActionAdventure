#pragma once

#include "InputActionValue.h"
#include "ActionAdventure/Character/AACharacter.h"
#include "AAPlayerCharacter.generated.h"

class UAAEquipmentComponent;
class USpringArmComponent;
class UCameraComponent;
class UInputMappingContext;
class UInputAction;

class UAAInventoryComponent;

UCLASS(config=Game)
class AAAPlayerCharacter : public AAACharacter
{
	GENERATED_BODY()

public:
	AAAPlayerCharacter();

	virtual void BeginPlay() override;

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	
	void Move(const FInputActionValue& Value);

	void Look(const FInputActionValue& Value);

	FORCEINLINE USpringArmComponent* GetCameraBoom() const { return CameraBoom; }
	FORCEINLINE UCameraComponent* GetFollowCamera() const { return FollowCamera; }

	UAAInventoryComponent* GetInventoryComponent() const {return InventoryComponent; }

	UAAEquipmentComponent* GetEquipmentComponent() const {return EquipmentComponent; }

	void PersistentModelSpawn();
	void PersistentModelDeserialize(const struct FAAPMStatePlayer& PMPlayer);
	
protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input)
	UInputMappingContext* DefaultMappingContext;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input)
	UInputAction* JumpAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input)
	UInputAction* MoveAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input)
	UInputAction* LookAction;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera)
	USpringArmComponent* CameraBoom;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera)
	UCameraComponent* FollowCamera;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Inventory")
	UAAInventoryComponent* InventoryComponent;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Inventory")
	UAAEquipmentComponent* EquipmentComponent;
	
};

