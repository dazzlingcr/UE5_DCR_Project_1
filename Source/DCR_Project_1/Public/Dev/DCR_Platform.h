#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "DCR_Project_1/DCR_Project_1.h"

#include "Components/BoxComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Components/TimelineComponent.h"

#include "DCR_Platform.generated.h"

UCLASS()
class DCR_PROJECT_1_API ADCR_Platform : public AActor
{
	GENERATED_BODY()
	
//PROPERTIES//

public:

	UPROPERTY(Replicated)
	UStaticMeshComponent* PlatformMesh;

	UPROPERTY(Replicated)
	UBoxComponent* BoxCollision;

	FVector PlatformScale = { 1.f, 1.f, 1.f };

	FVector CollisionScale = { 1.25f, 1.25f, 0.5f };

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Settings")
	float LiftingHeight = 240.f;
	
protected:

	int32 PlatformCounter;

	FTimeline TimeLine; 

	FTimerHandle TimerHandle;
	
	static const float DeltaTimeTimeLine;

	FVector PlatformLocation;

	virtual void GetLifetimeReplicatedProps(TArray<class FLifetimeProperty>& OutLifetimeProps) const override;

private:


//METHODS//

public:	

	ADCR_Platform();

protected:

	virtual void BeginPlay() override;

	UFUNCTION()
	void CollisionBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
	void CollisionEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

	UFUNCTION()
	void TickTimeLine();

	UFUNCTION()
	void TimeLineLiftUp(float Value);

private:

};
