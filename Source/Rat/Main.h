
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
	// Sets default values for this character's properties
	AMain();

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Camera", meta = (AllowPrivateAccess = "true"))
		class USpringArmComponent* CameraBoom;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Camera", meta = (AllowPrivateAccess = "true"))
		class UCameraComponent* Camera;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Equipment")
		TSubclassOf<AWeaponManager> EquippedBlade;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Animation")
		bool bIsPlayingAnim;
	bool RightHandEquipped;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	void MoveUp(float Value);
	void MoveRight(float Value);
	void StartSprint();
	void StopSprint();
	void EquipBlade();
};
