#include "DCR_PlayerController_1.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "GameFramework/Character.h"

void ADCR_PlayerController_1::BeginPlay()
{
	Super::BeginPlay();

	Player = Cast<ADCR_Character_1>(GetPawn());
	
	if (!Player)
	{
		return;
	}

	UEnhancedInputLocalPlayerSubsystem* lSubsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer());

	if (!lSubsystem)
	{
		return;
	}

	if (!IMC)
	{
		return;
	}

	lSubsystem->AddMappingContext(IMC, 0);
}

void ADCR_PlayerController_1::SetupInputComponent()
{
	Super::SetupInputComponent();

	UEnhancedInputComponent* lEnhancedInputComponent = Cast<UEnhancedInputComponent>(InputComponent);

	if (!lEnhancedInputComponent)
	{
		return;
	}

	lEnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &ADCR_PlayerController_1::Move);
	lEnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &ADCR_PlayerController_1::Look);
	lEnhancedInputComponent->BindAction(AttackAction, ETriggerEvent::Started, this, &ADCR_PlayerController_1::Attack);
}

void ADCR_PlayerController_1::Move(const FInputActionValue& Value)
{
	FVector2D lMovementVector = Value.Get<FVector2D>();

	const FRotator lRotation = GetControlRotation();
	const FRotator lYawRotation(0, lRotation.Yaw, 0);

	const FVector lForwardDirection = FRotationMatrix(lYawRotation).GetUnitAxis(EAxis::Y);
	const FVector lRightDirection = FRotationMatrix(lYawRotation).GetUnitAxis(EAxis::X);

	Player->AddMovementInput(lForwardDirection, lMovementVector.Y);
	Player->AddMovementInput(lRightDirection, lMovementVector.X);
}

void ADCR_PlayerController_1::Look(const FInputActionValue& Value)
{
	FVector2D lLookAxisVector = Value.Get<FVector2D>();

	AddYawInput(lLookAxisVector.X);
	AddPitchInput(lLookAxisVector.Y);
}

void ADCR_PlayerController_1::Attack()
{
	Player->Fire();
}
