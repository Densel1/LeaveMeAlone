// LeaveMeAlone Game by Netologia. All Gights Reserved.


#include "Weapon/LMABaseWeapon.h"
#include "Components/SkeletalMeshComponent.h"
#include "TimerManager.h"
//#include "Weapon/LMAWeaponComponent.h"

DEFINE_LOG_CATEGORY_STATIC(LogWeapon, All, All);

// Sets default values
ALMABaseWeapon::ALMABaseWeapon()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	WeaponComponent = CreateDefaultSubobject<USkeletalMeshComponent>("Weapon");
	SetRootComponent(WeaponComponent);

}

void ALMABaseWeapon::ChangeClip() {
	CurrentAmmoWeapon.Bullets = AmmoWeapon.Bullets;
}

// Called when the game starts or when spawned
void ALMABaseWeapon::BeginPlay()
{
	Super::BeginPlay();
	CurrentAmmoWeapon = AmmoWeapon;
}

void ALMABaseWeapon::DecrementBullets() {
	CurrentAmmoWeapon.Bullets--;
	UE_LOG(LogWeapon, Display, TEXT("Bullets = %s"), *FString::FromInt(CurrentAmmoWeapon.Bullets));

	if (IsCurrentClipEmpty())
	{
		stopFire();
		OnReload.Broadcast();
//		ChangeClip();
	}
}

void ALMABaseWeapon::oneShot() {
	Shoot();
}


bool ALMABaseWeapon::IsCurrentClipEmpty()
{
	return CurrentAmmoWeapon.Bullets <= 0;
}

bool ALMABaseWeapon::IsFullClip()
{
	return CurrentAmmoWeapon.Bullets == 30;
}


// Called every frame
void ALMABaseWeapon::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}


void ALMABaseWeapon::onFire() {

	GetWorldTimerManager().SetTimer(TimerHandle, this, &ALMABaseWeapon::oneShot, shootTimeRate, true);
//	if (IsCurrentClipEmpty())
//		ChangeClip();
}

void ALMABaseWeapon::stopFire() {
	GetWorldTimerManager().ClearTimer(TimerHandle);
}


void ALMABaseWeapon::Shoot() {
	GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Red, FString::Printf(TEXT("Fire %i"), CurrentAmmoWeapon.Bullets));
	const FTransform SocketTransform = WeaponComponent->GetSocketTransform("Muzzle");
	const FVector TraceStart = SocketTransform.GetLocation();
	const FVector ShootDirection = SocketTransform.GetRotation().GetForwardVector();
	const FVector TraceEnd = TraceStart + ShootDirection * TraceDistance;
	DrawDebugLine(GetWorld(), TraceStart, TraceEnd, FColor::Black, false, 1.0f, 0, 2.0f);
	FHitResult HitResult;
	GetWorld()->LineTraceSingleByChannel(HitResult, TraceStart, TraceEnd, ECollisionChannel::ECC_Visibility);
	if (HitResult.bBlockingHit)
	{
		DrawDebugSphere(GetWorld(), HitResult.ImpactPoint, 5.0f, 24, FColor::Red, false, 1.0f);
	}
	DecrementBullets();
}

