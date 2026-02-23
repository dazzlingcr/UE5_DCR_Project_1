#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "InputActionValue.h"
#include "DCR_Character_1.h"
#include "DCR_PlayerController_1.generated.h"

UCLASS()
class DCR_PROJECT_1_API ADCR_PlayerController_1 : public APlayerController
{
	GENERATED_BODY()

//METHODS//

public:


protected:

	virtual void BeginPlay() override;
	virtual void SetupInputComponent() override;

	void Move(const FInputActionValue& Value);
	void Look(const FInputActionValue& Value);
	void Attack();

private:


//PROPERTIES//

public:

	
protected:

	UPROPERTY(EditAnywhere, Category = "Input")
	class UInputMappingContext* IMC;

	UPROPERTY(EditAnywhere, Category = "Input")
	class UInputAction* MoveAction;

	UPROPERTY(EditAnywhere, Category = "Input")
	class UInputAction* LookAction;

	UPROPERTY(EditAnywhere, Category = "Input")
	class UInputAction* AttackAction;

	ADCR_Character_1* Player;

private:

	
};
