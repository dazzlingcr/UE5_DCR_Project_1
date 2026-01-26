#include "DCR_ItemActor_Test.h"
#include "Components/AudioComponent.h"

DEFINE_LOG_CATEGORY(DCR_ItemActor_Test)

ADCR_ItemActor_Test::ADCR_ItemActor_Test()
{
	PrimaryActorTick.bCanEverTick = false;

	AudioComponent = CreateDefaultSubobject<UAudioComponent>("AudioComponent_Test");
	AudioComponent->SetupAttachment(RootComponent);
}

void ADCR_ItemActor_Test::BeginPlay()
{
	Super::BeginPlay();
	
}

void ADCR_ItemActor_Test::SetSound_Implementation(UAudioComponent* Component)
{
		UE_LOG(DCR_ItemActor_Test, Warning, TEXT("Audio Component is missing"));
}

void ADCR_ItemActor_Test::GetComponentReference(UAudioComponent*& Component)
{
	Component = AudioComponent;
}