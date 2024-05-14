// LeaveMeAlone Game by Netologia. All Gights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "LMAHealthComponent.generated.h"


DECLARE_MULTICAST_DELEGATE(FOnDeath)
DECLARE_MULTICAST_DELEGATE_OneParam(FOnHealthChanged, float);


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class LEAVEMEALONE_API ULMAHealthComponent : public UActorComponent
{
	GENERATED_BODY()
private:
	float Health = 0.0f;

	UFUNCTION()
	void OnTakeAnyDamage(
		AActor* DamagedActor, float Damage, const class UDamageType* DamageType, class AController* InstigatedBy, AActor* DamageCauser);


public:	
	// Sets default values for this component's properties
	ULMAHealthComponent();

	UFUNCTION(BlueprintCallable)
	bool IsDead() const;


	UFUNCTION(BlueprintCallable)
	float GetHealth() const { return Health; }

	FOnDeath OnDeath;
	FOnHealthChanged OnHealthChanged;


	
	bool AddHealth(float NewHealth);
	bool IsHealthFull() const;
	


protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	float MaxHealth = 100.f;

public:	
	// Called every frame
//	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

		
};
