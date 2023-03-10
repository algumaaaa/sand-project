#include "WeaponManager.h"

AWeaponManager::AWeaponManager()
{
	PrimaryActorTick.bCanEverTick = true;
	WeaponMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Weapon"));
	WeaponMesh->SetupAttachment(GetRootComponent());
	// TODO change this for hitboxes?
	SetActorEnableCollision(false);
}

void AWeaponManager::BeginPlay()
{
	Super::BeginPlay();
}

void AWeaponManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

UAnimMontage* AWeaponManager::GetAttackAnimation(int Value)
{
	if (AttackA.IsValidIndex(Value)) {
		return AttackA[Value];
	}
	return NULL;
}