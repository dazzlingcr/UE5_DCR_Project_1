#include "Dev/DCR_Platform.h"
#include "Net/UnrealNetwork.h"

const float ADCR_Platform::DeltaTimeTimeLine = 0.005f;

void ADCR_Platform::GetLifetimeReplicatedProps(TArray<class FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(ADCR_Platform, PlatformMesh);
	DOREPLIFETIME(ADCR_Platform, BoxCollision);

}

ADCR_Platform::ADCR_Platform()
{
	bReplicates = true;

	PlatformMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Static Mesh"));
	const ConstructorHelpers::FObjectFinder<UStaticMesh> SM_Platform(TEXT("/Game/DCR_Project1/Levels/Lvl_1/_GENERATED/nikc/PlatformBox.PlatformBox"));
	PlatformMesh->SetStaticMesh(SM_Platform.Object);
	PlatformMesh->SetRelativeScale3D(PlatformScale);
	RootComponent = PlatformMesh;
	PlatformMesh->SetIsReplicated(true);

	BoxCollision = CreateDefaultSubobject<UBoxComponent>(TEXT("Collision"));
	BoxCollision->SetRelativeScale3D(CollisionScale);
	BoxCollision->SetupAttachment(RootComponent);

	const ConstructorHelpers::FObjectFinder<UCurveFloat> Curve(TEXT("/Game/DCR_Project1/Blueprints/C_LiftUp.C_LiftUp"));
	TimeLine = FTimeline{};
	FOnTimelineFloat ProgressFunction{};
	ProgressFunction.BindUFunction(this, "TimeLineLiftUp");
	TimeLine.AddInterpFloat(Curve.Object, ProgressFunction, FName{ TEXT("LiftingUp") });

	
	PrimaryActorTick.bCanEverTick = true;

}

void ADCR_Platform::BeginPlay()
{
	Super::BeginPlay();

	PlatformLocation = PlatformMesh->GetRelativeLocation();

	BoxCollision->OnComponentBeginOverlap.AddDynamic(this, &ADCR_Platform::CollisionBeginOverlap);
	BoxCollision->OnComponentEndOverlap.AddDynamic(this, &ADCR_Platform::CollisionEndOverlap);
}

void ADCR_Platform::CollisionBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (!HasAuthority())
	{
		return;
	}
	
	GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Yellow, TEXT("BeginOverlap"));

	TimeLine.Play();
	GetWorldTimerManager().SetTimer(TimerHandle, this, &ADCR_Platform::TickTimeLine, DeltaTimeTimeLine, true, 0.0f);

}

void ADCR_Platform::CollisionEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if (!HasAuthority())
	{
		return;
	}
	
	GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Yellow, TEXT("EndOverlap"));
	TimeLine.Reverse();
	GetWorldTimerManager().SetTimer(TimerHandle, this, &ADCR_Platform::TickTimeLine, DeltaTimeTimeLine, true, 0.0f);
}

void ADCR_Platform::TickTimeLine()
{
	if (TimeLine.IsPlaying())
	{
		TimeLine.TickTimeline(DeltaTimeTimeLine);
	}
	else
	{
		GetWorldTimerManager().ClearTimer(TimerHandle);
		SetLifeSpan(0);
	}
}

void ADCR_Platform::TimeLineLiftUp(float Value)
{
	float lZOffset = FMath::Lerp(0.f, LiftingHeight, Value);

	FVector lLocationOffset = { 0.f, 0.f, lZOffset };
	FVector lNewLocation = PlatformLocation + lLocationOffset;

	PlatformMesh->SetRelativeLocation(lNewLocation);
}

