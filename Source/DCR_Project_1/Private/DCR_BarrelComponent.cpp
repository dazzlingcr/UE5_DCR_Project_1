#include "DCR_BarrelComponent.h"

UDCR_BarrelComponent::UDCR_BarrelComponent()
{

	PrimaryComponentTick.bCanEverTick = true;

}

void UDCR_BarrelComponent::BeginPlay()
{
	Super::BeginPlay();
	
}

void UDCR_BarrelComponent::ShotLineTrace(FVector MuzzleLocation, FVector TraceEndLocation)
{
	FVector lTraceEndLocation = TraceEndLocation;

	FHitResult lHitResult;
	FCollisionQueryParams lQueryParams;
	lQueryParams.AddIgnoredActor(GetOwner());

	bool bHit = GetWorld()->LineTraceSingleByChannel(
		lHitResult,
		MuzzleLocation,
		TraceEndLocation,
		ECC_Visibility,
		lQueryParams
	);

	if (bHit)
	{
		lTraceEndLocation = lHitResult.Location;
	}

	DrawDebugLine(GetWorld(), MuzzleLocation, lTraceEndLocation, FColor::Yellow, false, 0.3f, 0, 0.5f);
}

void UDCR_BarrelComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

}

