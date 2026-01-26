#pragma once

#include "CoreMinimal.h"
#include "ECPP_ItemTypes.generated.h"

UENUM(BlueprintType)
enum class ECPP_ItemTypes : uint8
{
	Gun UMETA(DisplayName = "Gun"),
	Equipment UMETA(DisplayName = "Equipment"),
	Ammo UMETA(DisplayName = "Ammo"),
};
