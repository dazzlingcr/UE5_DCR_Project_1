#include "DCR_Turret.h"
#include "DCR_BarrelComponent.h"

ADCR_Turret::ADCR_Turret()
{
	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMesh"));
	StaticMesh->SetupAttachment(RootComponent);
	
	PrimaryActorTick.bCanEverTick = true;

}

void ADCR_Turret::BeginPlay()
{
	Super::BeginPlay();

	BarrelComponent = FindComponentByClass<UDCR_BarrelComponent>();
	if (BarrelComponent)
	{
		GetWorld()->GetTimerManager().SetTimer(FireTimer, this, &ADCR_Turret::Fire, FireRate, true);
	}
	
}

void ADCR_Turret::Fire()
{
	TraceStartLocation = StaticMesh->GetComponentLocation();
	TraceEndLocation = TraceStartLocation + (StaticMesh->GetForwardVector() * TraceRange); 
	
	BarrelComponent->ShotLineTrace(TraceStartLocation, TraceEndLocation);
}

void ADCR_Turret::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

