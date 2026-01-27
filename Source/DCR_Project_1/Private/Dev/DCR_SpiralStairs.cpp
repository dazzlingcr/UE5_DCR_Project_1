#include "Dev/DCR_SpiralStairs.h"

ADCR_SpiralStairs::ADCR_SpiralStairs()
{
	PrimaryActorTick.bCanEverTick = false;

	USceneComponent* RootSceneComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent"));
	RootComponent = RootSceneComponent;

}

void ADCR_SpiralStairs::OnConstruction(const FTransform& Transform)
{
	Super::OnConstruction(Transform);

	StairsConstruction();
}

void ADCR_SpiralStairs::BeginPlay()
{
	Super::BeginPlay();

}

void ADCR_SpiralStairs::StairsConstruction()
{
	DestroyStairComponents();

	if (!StepMesh or !ColumnMesh)
	{
		UE_LOG(LogTemp, Warning, TEXT("Meshes must be specified!"));
		return;
	}

	int32 lStepsTotal = NumberOfTurn * StepsPerTurn;
	float lStepsAngle = 360.0f / StepsPerTurn;

	for (int32 i = 0; i < lStepsTotal; i++)
	{
		FString lStepName = FString::Printf(TEXT("Step_%d"), i);
		UStaticMeshComponent* lStep = NewObject<UStaticMeshComponent>(this, *lStepName);

		lStep->SetStaticMesh(StepMesh);
		lStep->SetupAttachment(RootComponent);

		float lAngle = FMath::DegreesToRadians(i * lStepsAngle);

		float X = FMath::Cos(lAngle) * Radius;
		float Y = FMath::Sin(lAngle) * Radius;
		float Z = i * HeightBeetweenSteps;

		FVector lStepLocation = { X, Y, Z };
		FRotator lStepRotation = { 0, i * lStepsAngle, 0 };

		lStep->SetRelativeLocation(lStepLocation);
		lStep->SetRelativeRotation(lStepRotation);
		lStep->SetRelativeScale3D(StepScale);

		lStep->RegisterComponent();

		StairsComponents.Add(lStep);
	}

	UStaticMeshComponent* lColumn = NewObject<UStaticMeshComponent>(this, "Column");

	lColumn->SetStaticMesh(ColumnMesh);
	lColumn->SetupAttachment(RootComponent);

	float lColumnHeight = ColumnMesh->GetBoundingBox().GetExtent().Z * 2.f;

	FTransform lStepTransform = StairsComponents[0]->GetComponentTransform();
	FBoxSphereBounds lStepBounds = StairsComponents[0]->CalcBounds(lStepTransform);
	float lStepHalfHeight = lStepBounds.BoxExtent.Z;
	float lStepHalfWidth = lStepBounds.BoxExtent.X;
	float lLastStepLocationZ = (lStepsTotal - 1) * HeightBeetweenSteps;
	float lStairsHeight = lLastStepLocationZ + lStepHalfHeight * 2.f;
	
	FVector lColomnLocation = { 0, 0, (lStairsHeight / 2.f - lStepHalfHeight) };

	lColumn->SetRelativeLocation(lColomnLocation);

	float lColumnRadius = ColumnMesh->GetBoundingBox().GetExtent().X;

	int32 lColumnOffset = ColumnOffset;

	if (ColumnOffset > 0 && ColumnOffset >= Radius)
	{
		lColumnOffset = Radius;
	}
	else if (ColumnOffset < 0 && std::abs(ColumnOffset) >= lStepHalfWidth)
	{
		lColumnOffset = -lStepHalfWidth;
	}

	float lColumnScaleMultiplierXY = (Radius - lColumnOffset) / lColumnRadius;
	float lColumnScaleMultiplierZ = lStairsHeight / lColumnHeight;
	FVector lColumnScaleZMultiplier = { lColumnScaleMultiplierXY, lColumnScaleMultiplierXY, lColumnScaleMultiplierZ };

	lColumn->SetRelativeScale3D(lColumnScaleZMultiplier);


	lColumn->RegisterComponent();
	StairsComponents.Add(lColumn);

}

void ADCR_SpiralStairs::DestroyStairComponents()
{
	for (UStaticMeshComponent* Comp : StairsComponents)
	{
		if (Comp)
		{
			Comp->DestroyComponent();

		}
	}
}

void ADCR_SpiralStairs::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}
