// LeaveMeAlone Game by Netologia. All Gights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"

#include "LMABaseWeapon.generated.h"

class USkeletalMeshComponent;

DECLARE_MULTICAST_DELEGATE(FOnReload)

USTRUCT(BlueprintType)
struct FAmmoWeapon
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Weapon")
	int32 Bullets;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Weapon")
	int32 Clips;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Weapon")
	bool Infinite;
};



UCLASS()
class LEAVEMEALONE_API ALMABaseWeapon : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ALMABaseWeapon();

	UFUNCTION(BlueprintCallable)
	void ChangeClip();

    FOnReload OnReload;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Weapon")
	USkeletalMeshComponent* WeaponComponent;

		UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Weapon")
	float TraceDistance = 800.0f;

	void Shoot();

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Weapon")
	FAmmoWeapon AmmoWeapon{30, 0, true};

	void DecrementBullets();

	void oneShot();
		
	FTimerHandle TimerHandle;


public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void onFire();

	UFUNCTION(BlueprintCallable)
	void stopFire();

	UFUNCTION(BlueprintCallable)
	bool IsCurrentClipEmpty();

	bool IsFullClip();

	FAmmoWeapon GetCurrentAmmoWeapon() const { return CurrentAmmoWeapon; }

private:
	FAmmoWeapon CurrentAmmoWeapon;
	float shootTimeRate = 0.1f;
};
