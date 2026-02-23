#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "DCR_BaseWeapon_1.generated.h"

UCLASS()
class DCR_PROJECT_1_API ADCR_BaseWeapon_1 : public AActor
{
	GENERATED_BODY()
	

	//METHODS//

public:

	virtual void Tick(float DeltaTime) override;

	void Fire(FVector TraceEndLocation);

protected:

	virtual void BeginPlay() override;

	FVector SetMuzzleSocketLocation();

private:




	//PROPERTIES//

public:

	ADCR_BaseWeapon_1();

protected:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon")
	int32 Ammo = 100;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon")
	UStaticMeshComponent* StaticMesh;

	UPROPERTY(BlueprintReadOnly)
	FVector MuzzleLocation;

	UPROPERTY(BlueprintReadOnly)
	FName MuzzleSocketName = FName("Muzzle");

private:



};