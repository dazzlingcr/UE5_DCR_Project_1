#include "DCR_Character_1.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "Components/SceneComponent.h"

ADCR_Character_1::ADCR_Character_1()
{
	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("Default Spring Arm"));
	SpringArm->SetupAttachment(RootComponent);
	SpringArm->TargetArmLength = 500.f;
	SpringArm->bUsePawnControlRotation = true;

	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Default Camera"));
	Camera->SetupAttachment(SpringArm, USpringArmComponent::SocketName);

	WeaponSocket = CreateDefaultSubobject<USceneComponent>(TEXT("Default Weapon Socket"));
	WeaponSocket->SetupAttachment(RootComponent);

	PrimaryActorTick.bCanEverTick = true;

}

void ADCR_Character_1::BeginPlay()
{
	Super::BeginPlay();

	WeaponSpawn();

}

void ADCR_Character_1::WeaponSpawn()
{
	if (WeaponClass)
	{
		FActorSpawnParameters lSpawnParams;
		lSpawnParams.Owner = this;
		lSpawnParams.Instigator = GetInstigator();

		CurrentWeapon = GetWorld()->SpawnActor<ADCR_BaseWeapon_1>(WeaponClass, FVector::ZeroVector, FRotator::ZeroRotator, lSpawnParams);

		if (CurrentWeapon)
		{
			CurrentWeapon->AttachToComponent(WeaponSocket, FAttachmentTransformRules::SnapToTargetNotIncludingScale, FName("WeaponSocket"));
		}
	}
}

FVector ADCR_Character_1::GetViewPointLocation()
{
	FVector lTraceStart = Camera->GetComponentLocation();
	FVector lCameraForwardVector = Camera->GetForwardVector();

	float lTraceRange = 2000.f;
	FVector lTraceEnd = lTraceStart + (lCameraForwardVector * lTraceRange);

	FHitResult lHitResult;
	FCollisionQueryParams lQueryParams;
	lQueryParams.AddIgnoredActor(this);

	bool bHit = GetWorld()->LineTraceSingleByChannel(
		lHitResult,
		lTraceStart,
		lTraceEnd,
		ECC_Visibility,
		lQueryParams
	);

	if (bHit)
	{
		lTraceEnd = lHitResult.Location;
	}
	
	return lTraceEnd;
}

void ADCR_Character_1::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	ViewPoint = GetViewPointLocation();

}

void ADCR_Character_1::Fire()
{
	if (!CurrentWeapon)
	{
		return;
	}

	CurrentWeapon->Fire(ViewPoint);
}