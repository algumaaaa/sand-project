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

TArray<UAnimMontage*> AWeaponManager::GetAttackBranch(int Value)
{
	switch (Value) {
	case 0:
		return AttackA;
	case 1:
		return AttackB;
	default:
		return AttackA;
	}
}

void AWeaponManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

UAnimMontage* AWeaponManager::GetAttackAnimation(int Value, int Branch)
{
	TArray<UAnimMontage*> AttackBranch = GetAttackBranch(Branch);
	if (AttackBranch.IsValidIndex(Value)) {
		return AttackBranch[Value];
	}
	return NULL;
}