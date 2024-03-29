
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "WeaponManager.h"
#include "Main.generated.h"



UCLASS()
class RAT_API AMain : public ACharacter
{
	GENERATED_BODY()

public:
	AMain();

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Camera", meta = (AllowPrivateAccess = "true"))
		class USpringArmComponent* CameraBoom;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Camera", meta = (AllowPrivateAccess = "true"))
		class UCameraComponent* Camera;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Equipment")
		TSubclassOf<AWeaponManager> EquippedBlade;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Animation")
		bool bIsPlayingAnim;
	UPROPERTY(BlueprintReadOnly)
	bool RightHandEquipped;
	UPROPERTY(BlueprintReadOnly)
	AWeaponManager* SpawnedBlade;
	UPROPERTY(BlueprintReadWrite, Category = "Animation")
		int ComboIterator = 0;
	UPROPERTY(BlueprintReadWrite, Category = "Animation")
		int AttackBranch = 0;

protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	virtual void Jump() override;
	void MoveUp(float Value);
	void MoveRight(float Value);
	void StartSprint();
	void StopSprint();
	void EquipBlade();
	void SheatheBlade();
	void UnsheatheBlade();
	void Attack();
	UFUNCTION(BlueprintCallable, Category = "Animation")
	void ResetAttack();
	UFUNCTION(BlueprintCallable, Category = "Animation")
	void IterateAttack();
	UFUNCTION(BlueprintCallable, Category = "Animation")
	void BranchAttack();

private:
	UPROPERTY()
		bool CanAttack = true;
	UPROPERTY()
		bool IsGroundAttacking = false;
	UPROPERTY()
		FTimerHandle TimerHandle;
};
