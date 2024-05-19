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
	GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Red, FString::Printf(TEXT("OnNotifyReloadFinished")));
	const auto Character = Cast<ACharacter>(GetOwner());
	if (Character->GetMesh() == SkeletalMesh)
	{
		AnimReloading = false;
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
//	isShooting = true;

	if (Weapon&&!AnimReloading)
	{
		if (!Weapon->IsCurrentClipEmpty())
		Weapon->onFire();

//		{
//			isShooting = false;
			
//			Reload();
//		}

	}
}

void ULMAWeaponComponent::Reload() {
	GEngine->AddOnScreenDebugMessage(-1, 20.0f, FColor::Red, FString::Printf(TEXT("TryReload")));
	if (!CanReload())
		return;
	GEngine->AddOnScreenDebugMessage(-1, 20.0f, FColor::Red, FString::Printf(TEXT("Reload")));
	AnimReloading = true;
	ACharacter* Character = Cast<ACharacter>(GetOwner());
	Character->PlayAnimMontage(ReloadMontage);
	Weapon->ChangeClip();
}

void ULMAWeaponComponent::StopFire() {

//	isShooting = false;
	Weapon->stopFire();
}
