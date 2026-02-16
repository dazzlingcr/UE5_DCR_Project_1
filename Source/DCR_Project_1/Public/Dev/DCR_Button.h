#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"

#include "Components/BoxComponent.h"
#include "Components/StaticMeshComponent.h"
#include "NiagaraFunctionLibrary.h"
#include "NiagaraComponent.h"

#include "DCR_Button.generated.h"

UCLASS()
class DCR_PROJECT_1_API ADCR_Button : public AActor
{
	GENERATED_BODY()
	
	//PROPERTIES//

public:

	UStaticMeshComponent* PlatformMesh;

	UBoxComponent* BoxCollision;

	FVector PlatformScale = { 1.f, 1.f, 1.f };

	FVector CollisionScale = { 1.25f, 1.25f, 0.5f };

	UNiagaraSystem* NiagaraAsset;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	FVector NiagaraLocation = { 15.f, -1360.f, 595.f };

protected:



private:



	//METHODS//

public:	
	
	ADCR_Button();

protected:

	virtual void BeginPlay() override;

	UFUNCTION()
	void CollisionBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
	void CollisionEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

private:	

	virtual void Tick(float DeltaTime) override;

};
