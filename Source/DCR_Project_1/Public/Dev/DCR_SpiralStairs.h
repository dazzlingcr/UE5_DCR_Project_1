#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"

#include "DCR_SpiralStairs.generated.h"

UCLASS()
class DCR_PROJECT_1_API ADCR_SpiralStairs : public APawn
{
	GENERATED_BODY()

public:
	ADCR_SpiralStairs();

	UPROPERTY(EditInstanceOnly, BlueprintReadOnly, Category = "StairsSettings")
	UStaticMesh* StepMesh;

	UPROPERTY(EditInstanceOnly, BlueprintReadOnly, Category = "StairsSettings")
	UStaticMesh* ColumnMesh;

	UPROPERTY(EditInstanceOnly, BlueprintReadOnly, Category = "StairsSettings", meta = (ClampMin = "1", ClampMax = "1000"))
	int32 HeightBeetweenSteps = 15;

	UPROPERTY(EditInstanceOnly, BlueprintReadOnly, Category = "StairsSettings", meta = (ClampMin = "0.1", ClampMax = "2"))
	FVector StepScale = { 0.75f, 0.45f, 0.2f };

	UPROPERTY(EditInstanceOnly, BlueprintReadOnly, Category = "StairsSettings", meta = (ClampMin = "0", ClampMax = "1000"))
	int32 Radius = 120;

	UPROPERTY(EditInstanceOnly, BlueprintReadOnly, Category = "StairsSettings", meta = (ClampMin = "-999", ClampMax = "999", ToolTip = "DefaultValue = 0; If this value is greater than the Radius, the column will not exist."))
	int32 ColumnOffset = 70;

	UPROPERTY(EditInstanceOnly, BlueprintReadOnly, Category = "StairsSettings", meta = (ClampMin = "3", ClampMax = "128"))
	int32 StepsPerTurn = 22;

	UPROPERTY(EditInstanceOnly, BlueprintReadOnly, Category = "StairsSettings", meta = (ClampMin = "1", ClampMax = "10"))
	int32 NumberOfTurn = 1;


protected:
	virtual void BeginPlay() override;

	virtual void OnConstruction(const FTransform& Transform) override;
	void StairsConstruction();
	void DestroyStairComponents();

private:
	TArray<UStaticMeshComponent*> StairsComponents;

public:	
	virtual void Tick(float DeltaTime) override;

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};
