#include "DCR_BaseWeapon_1.h"
#include "DCR_BarrelComponent.h"

ADCR_BaseWeapon_1::ADCR_BaseWeapon_1()
{
	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("WeaponStaticMesh"));
	StaticMesh->SetupAttachment(RootComponent);

	PrimaryActorTick.bCanEverTick = true;

}

void ADCR_BaseWeapon_1::BeginPlay()
{
	Super::BeginPlay();

}

FVector ADCR_BaseWeapon_1::SetMuzzleSocketLocation()
{
	FVector lMuzzleLocation;

	if (StaticMesh->DoesSocketExist(MuzzleSocketName))
	{
		lMuzzleLocation = StaticMesh->GetSocketLocation(MuzzleSocketName);
	}
	else
	{
		lMuzzleLocation = StaticMesh->GetComponentLocation();
	}

	return lMuzzleLocation;
}

void ADCR_BaseWeapon_1::Fire(FVector TraceEndLocation)
{
	UDCR_BarrelComponent* lBarrelComponent = FindComponentByClass<UDCR_BarrelComponent>();

	if (!StaticMesh || !lBarrelComponent)
	{
		return;
	}
	
	if (Ammo <= 0)
	{
		return;
	}

	Ammo = Ammo - 1;

	lBarrelComponent->ShotLineTrace(SetMuzzleSocketLocation(), TraceEndLocation);

}

void ADCR_BaseWeapon_1::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}