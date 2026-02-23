#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "DCR_BaseWeapon_1.h"
#include "DCR_Character_1.generated.h"

class ADCR_BaseWeapon_1;

UCLASS()
class DCR_PROJECT_1_API ADCR_Character_1 : public ACharacter
{
	GENERATED_BODY()


	//METHODS//

public:

	virtual void Tick(float DeltaTime) override;

	void Fire();


protected:
	
	virtual void BeginPlay() override;

	void WeaponSpawn();

	FVector GetViewPointLocation();


private:



	//PROPERTIES//

public:
	
	ADCR_Character_1();


protected:

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Camera")
	class USpringArmComponent* SpringArm;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Camera")
	class UCameraComponent* Camera;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Weapon")
	class USceneComponent* WeaponSocket;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Weapon")
	TSubclassOf<ADCR_BaseWeapon_1> WeaponClass;

	UPROPERTY(BlueprintReadOnly)
	ADCR_BaseWeapon_1* CurrentWeapon;

	UPROPERTY(BlueprintReadOnly)
	FVector ViewPoint;

private:



};
