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

	int32 StepsTotal = NumberOfTurn * StepsPerTurn;
	float StepsAngle = 360.0f / StepsPerTurn;

	for (int32 i = 0; i < StepsTotal; i++)
	{
		FString StepName = FString::Printf(TEXT("Step_%d"), i);
		UStaticMeshComponent* Step = NewObject<UStaticMeshComponent>(this, *StepName);

		Step->SetStaticMesh(StepMesh);
		Step->SetupAttachment(RootComponent);

		float Angle = FMath::DegreesToRadians(i * StepsAngle);

		float X = FMath::Cos(Angle) * Radius;
		float Y = FMath::Sin(Angle) * Radius;
		float Z = i * HeightBeetweenSteps;

		FVector StepLocation = { X, Y, Z };
		FRotator StepRotation = { 0, i * StepsAngle, 0 };

		Step->SetRelativeLocation(StepLocation);
		Step->SetRelativeRotation(StepRotation);
		Step->SetRelativeScale3D(StepScale);

		Step->RegisterComponent();

		StairsComponents.Add(Step);
	}

	UStaticMeshComponent* Column = NewObject<UStaticMeshComponent>(this, "Column");

	Column->SetStaticMesh(ColumnMesh);
	Column->SetupAttachment(RootComponent);

	float ColumnHeight = ColumnMesh->GetBoundingBox().GetExtent().Z * 2.f;

	FTransform StepTransform = StairsComponents[0]->GetComponentTransform();
	FBoxSphereBounds StepBounds = StairsComponents[0]->CalcBounds(StepTransform);
	float StepHalfHeight = StepBounds.BoxExtent.Z;
	float StepHalfWidth = StepBounds.BoxExtent.X;
	float LastStepLocationZ = (StepsTotal - 1) * HeightBeetweenSteps;
	float StairsHeight = LastStepLocationZ + StepHalfHeight * 2.f;
	
	FVector ColomnLocation = { 0, 0, (StairsHeight / 2.f - StepHalfHeight) };

	Column->SetRelativeLocation(ColomnLocation);

	float ColumnRadius = ColumnMesh->GetBoundingBox().GetExtent().X;

	int32 lColumnOffset = ColumnOffset;

	if (ColumnOffset > 0 && ColumnOffset >= Radius)
	{
		lColumnOffset = Radius;
	}
	else if (ColumnOffset < 0 && std::abs(ColumnOffset) >= StepHalfWidth)
	{
		lColumnOffset = -StepHalfWidth;
	}

	float ColumnScaleMultiplierXY = (Radius - lColumnOffset) / ColumnRadius;
	float ColumnScaleMultiplierZ = StairsHeight / ColumnHeight;
	FVector ColumnScaleZMultiplier = { ColumnScaleMultiplierXY, ColumnScaleMultiplierXY, ColumnScaleMultiplierZ };

	Column->SetRelativeScale3D(ColumnScaleZMultiplier);


	Column->RegisterComponent();
	StairsComponents.Add(Column);

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
