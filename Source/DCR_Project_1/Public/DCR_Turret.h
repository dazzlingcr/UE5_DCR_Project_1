#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "DCR_Turret.generated.h"

UCLASS()
class DCR_PROJECT_1_API ADCR_Turret : public AActor
{
	GENERATED_BODY()
	

	//METHODS//


public:	

	ADCR_Turret();

	void Fire();

protected:

	virtual void BeginPlay() override;

public:	

	virtual void Tick(float DeltaTime) override;


	//PROPERTIES//

public:


protected:

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "StaticMesh")
	UStaticMeshComponent* StaticMesh;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "TraceRange")
	float TraceRange = 2000.f;

	FVector TraceStartLocation;
	FVector TraceEndLocation;

	class UDCR_BarrelComponent* BarrelComponent;

	FTimerHandle FireTimer;
	float FireRate = 0.25f;

public:


};
