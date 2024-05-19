// LeaveMeAlone Game by Netologia. All Gights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Animations/LMAReloadFinishedAnimNotify.h"


#include "LMAWeaponComponent.generated.h"

class ALMABaseWeapon;
class UAnimMontage;


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class LEAVEMEALONE_API ULMAWeaponComponent : public UActorComponent
{
	GENERATED_BODY()

public:	

	ULMAWeaponComponent();

	void Fire();
	void Reload();
	void StopFire();



protected:

	virtual void BeginPlay() override;

	UPROPERTY(EditDefaultsOnly, Category = "Weapon")
	TSubclassOf<ALMABaseWeapon> WeaponClass;

	UPROPERTY()
	ALMABaseWeapon* Weapon = nullptr;

	UPROPERTY(EditDefaultsOnly, Category = "Weapon")
	UAnimMontage* ReloadMontage;





public:	

	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

		void oneShot();

private:




	bool AnimReloading = false;

	void SpawnWeapon();
	void InitAnimNotify();

	void OnNotifyReloadFinished(USkeletalMeshComponent* SkeletalMesh);
	bool CanReload() const;

	bool isShooting = false;


	void broadcastReciever();


};
