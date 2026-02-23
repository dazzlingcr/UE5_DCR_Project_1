#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "DCR_BarrelComponent.generated.h"


UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent, DisplayName = "Barrel Component"))
class DCR_PROJECT_1_API UDCR_BarrelComponent : public UActorComponent
{
	GENERATED_BODY()

	//METHODS//

public:
	
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	void ShotLineTrace(FVector MuzzleLocation, FVector TraceEndLocation);

protected:

	virtual void BeginPlay() override;

private:



	//PROPERTIES//

public:

	UDCR_BarrelComponent();

protected:


private:

};