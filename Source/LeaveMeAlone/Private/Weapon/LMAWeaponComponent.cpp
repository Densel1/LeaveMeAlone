// LeaveMeAlone Game by Netologia. All Gights Reserved.

#include "Weapon/LMABaseWeapon.h"
#include "Animations/LMAReloadFinishedAnimNotify.h"
#include "GameFramework/Character.h"
#include "Weapon/LMAWeaponComponent.h"






ULMAWeaponComponent::ULMAWeaponComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}


// Called when the game starts
void ULMAWeaponComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	SpawnWeapon();
	InitAnimNotify();
//
}


// Called every frame
void ULMAWeaponComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

}

void ULMAWeaponComponent::oneShot() {
	Weapon->onFire();
}

bool ULMAWeaponComponent::GetCurrentWeaponAmmo(FAmmoWeapon& AmmoWeapon) const
{
	if (Weapon)
	{
		AmmoWeapon = Weapon->GetCurrentAmmoWeapon();
		return true;
	}
	return false;
}

void ULMAWeaponComponent::SpawnWeapon()
{
	Weapon = GetWorld()->SpawnActor<ALMABaseWeapon>(WeaponClass);
	Weapon->OnReload.AddUObject(this, &ULMAWeaponComponent::broadcastReciever); 

	if (Weapon)
	{
		const auto Character = Cast<ACharacter>(GetOwner());
		if (Character)
		{
			FAttachmentTransformRules AttachmentRules(EAttachmentRule::SnapToTarget, false);
			Weapon->AttachToComponent(Character->GetMesh(), AttachmentRules, "r_Weapon_Socket");
		}
	}
}

void ULMAWeaponComponent::InitAnimNotify() {


	if (!ReloadMontage)
		return;

	const /* FAnimNotifyEvent*/ auto NotifiesEvents = ReloadMontage->Notifies;
	for (auto NotifyEvent : NotifiesEvents)
	{
		auto ReloadFinish = Cast<ULMAReloadFinishedAnimNotify>(NotifyEvent.Notify);


		if (ReloadFinish)
		{
			ReloadFinish->OnNotifyReloadFinished.AddUObject(this, &ULMAWeaponComponent::OnNotifyReloadFinished);

			break;
		}
	}
}

void ULMAWeaponComponent::OnNotifyReloadFinished(USkeletalMeshComponent* SkeletalMesh) {

	const auto Character = Cast<ACharacter>(GetOwner());
	if (Character->GetMesh() == SkeletalMesh)
	{
		AnimReloading = false;
		Weapon->ChangeClip();
	}
}

bool ULMAWeaponComponent::CanReload() const
{
	bool ableToReload = 1;
	if (AnimReloading || Weapon->IsFullClip())
		ableToReload = false;

	return ableToReload;
}

void ULMAWeaponComponent::broadcastReciever() {
	Reload();
}

void ULMAWeaponComponent::Fire()
{
	if (Weapon&&!AnimReloading)
	{
		if (!Weapon->IsCurrentClipEmpty())
		Weapon->onFire();
	}
}

void ULMAWeaponComponent::Reload() {

	if (!CanReload())
		return;
	AnimReloading = true;
	ACharacter* Character = Cast<ACharacter>(GetOwner());
	Character->PlayAnimMontage(ReloadMontage);

}

void ULMAWeaponComponent::StopFire() {

	Weapon->stopFire();
}
