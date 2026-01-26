#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ECPP_ItemTypes.h"
#include "Components/AudioComponent.h"

#include "DCR_ItemActor_Test.generated.h"

DECLARE_LOG_CATEGORY_EXTERN(DCR_ItemActor_Test, All, All)

UCLASS()
class DCR_PROJECT_1_API ADCR_ItemActor_Test : public AActor
{
	GENERATED_BODY()
	
public:	
	ADCR_ItemActor_Test();

	UPROPERTY(EditInstanceOnly, BlueprintReadOnly, Category = "ItemProperties")
	ECPP_ItemTypes ItemType;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (ClampMin = 0, ClampMax = 6), Category = "ItemProperties")
	int32 Amount;

	UPROPERTY(VisibleInstanceOnly, BlueprintReadWrite, Category = "ItemProperties")
	bool bIsForSale;

	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, meta = (ExposeOnSpawn = true), Category = "ItemProperties")
	bool bIsRare;

	UPROPERTY(EditInstanceOnly, BlueprintReadOnly, Category = "ItemProperties")
	bool bIsQuestItem;


	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent)
	void PrintComponentName(UAudioComponent* Component);


	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void SetSound(UAudioComponent* Component);

	void SetSound_Implementation(UAudioComponent* Component);


	UFUNCTION(BlueprintCallable)
	void GetComponentReference(UPARAM(DisplayName = "Audio Component") UAudioComponent*& Component);


protected:
	virtual void BeginPlay() override;

	UPROPERTY (VisibleAnywhere, BlueprintReadWrite)
	UAudioComponent* AudioComponent;
};
