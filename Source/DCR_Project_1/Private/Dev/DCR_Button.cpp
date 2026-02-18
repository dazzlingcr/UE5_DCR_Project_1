#include "Dev/DCR_Button.h"

ADCR_Button::ADCR_Button()
{
	bReplicates = true;

	PlatformMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Static Mesh"));
	const ConstructorHelpers::FObjectFinder<UStaticMesh> SM_Platform(TEXT("/Game/DCR_Project1/Levels/Lvl_1/_GENERATED/nikc/PlatformBox.PlatformBox"));
	PlatformMesh->SetStaticMesh(SM_Platform.Object);
	PlatformMesh->SetRelativeScale3D(PlatformScale);
	RootComponent = PlatformMesh;

	BoxCollision = CreateDefaultSubobject<UBoxComponent>(TEXT("Collision"));
	BoxCollision->SetRelativeScale3D(CollisionScale);
	BoxCollision->SetupAttachment(RootComponent);

	const ConstructorHelpers::FObjectFinder<UNiagaraSystem> Asset(TEXT("/Game/DCR_Project1/Blueprints/NS_NIaGAra.NS_NIaGAra"));
	NiagaraAsset = Asset.Object;

	PrimaryActorTick.bCanEverTick = false;

}

void ADCR_Button::BeginPlay()
{
	Super::BeginPlay();
	
	BoxCollision->OnComponentBeginOverlap.AddDynamic(this, &ADCR_Button::CollisionBeginOverlap);
	BoxCollision->OnComponentEndOverlap.AddDynamic(this, &ADCR_Button::CollisionEndOverlap);
}

void ADCR_Button::CollisionBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (!HasAuthority())
	{
		return;
	}
		
	APawn* lInteractingCharacter = Cast<APawn>(OtherActor);
	if (lInteractingCharacter)
	{
		NetMulticast_NiagaraSystem();
	}
}

void ADCR_Button::CollisionEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	
}

void ADCR_Button::NetMulticast_NiagaraSystem_Implementation()
{
	if (!HasAuthority())
	{
		UNiagaraFunctionLibrary::SpawnSystemAtLocation(GetWorld(), NiagaraAsset, NiagaraLocation, FRotator::ZeroRotator);
	}
}