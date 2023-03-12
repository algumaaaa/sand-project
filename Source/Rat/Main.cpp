
#include "Main.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "Engine/World.h"
#include "GameFramework/CharacterMovementComponent.h"

AMain::AMain()
{
	PrimaryActorTick.bCanEverTick = true;

	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(GetRootComponent());
	CameraBoom->TargetOffset = FVector(0, 0, 55);
	CameraBoom->bUsePawnControlRotation = true;

	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->bUsePawnControlRotation = false;
	Camera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);

	bUseControllerRotationYaw = false;
	bUseControllerRotationPitch = false;
	bUseControllerRotationRoll = false;
	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->RotationRate = FRotator(0.f, 500.f, 0.f);
}

void AMain::BeginPlay()
{
	Super::BeginPlay();

}

void AMain::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AMain::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	InputComponent->BindAxis("MoveUp", this, &AMain::MoveUp);
	InputComponent->BindAxis("MoveRight", this, &AMain::MoveRight);
	InputComponent->BindAxis("LookYaw", this, &APawn::AddControllerYawInput);
	InputComponent->BindAxis("LookPitch", this, &APawn::AddControllerPitchInput);
	InputComponent->BindAction("Sprint", IE_Pressed, this, &AMain::StartSprint);
	InputComponent->BindAction("Sprint", IE_Released, this, &AMain::StopSprint);
	InputComponent->BindAction("Jump", IE_Pressed, this, &AMain::Jump);
	InputComponent->BindAction("Attack", IE_Pressed, this, &AMain::Attack);
	InputComponent->BindAction("DEBUG_1", IE_Pressed, this, &AMain::EquipBlade);

}

void AMain::Jump()
{
	if (!IsGroundAttacking) {
		Super::Jump();
	}
}

void AMain::MoveUp(float Value)
{
	if (Controller == nullptr || Value == 0.f || bIsPlayingAnim) { return; }

	const FRotator Rotation = Controller->GetControlRotation();
	const FRotator YawRotation(0.f, Rotation.Yaw, 0.f);
	const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);

	AddMovementInput(Direction, Value);
}

void AMain::MoveRight(float Value)
{
	if (Controller == nullptr || Value == 0.f || bIsPlayingAnim) { return; }

	const FRotator Rotation = Controller->GetControlRotation();
	const FRotator YawRotation(0.f, Rotation.Yaw, 0.f);
	const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

	AddMovementInput(Direction, Value);
}

void AMain::StartSprint()
{
	GetCharacterMovement()->MaxWalkSpeed = 1050.f;
}

void AMain::StopSprint()
{
	GetCharacterMovement()->MaxWalkSpeed = 650.f;
}

void AMain::EquipBlade()
{
	if (EquippedBlade == nullptr) { return; }
	if (!RightHandEquipped) {
		FName Socket = "SOC_Blade";
		// Spawn the weapon at the socket transform
		FVector Loc = GetMesh()->GetSocketLocation(Socket);
		FRotator Rot = GetMesh()->GetSocketRotation(Socket);
		FActorSpawnParameters Params;
		Params.Name = "Blade";
		SpawnedBlade = GetWorld()->SpawnActor<AWeaponManager>(EquippedBlade, Loc, Rot, Params);
		// Attach to socket
		SheatheBlade(); // TODO: Change this to hand later?
		RightHandEquipped = true;
	}
}

void AMain::SheatheBlade()
{
	// Attach blade to back socket
	if (SpawnedBlade == nullptr) { return; }
	SpawnedBlade->AttachToComponent(GetMesh(), FAttachmentTransformRules::SnapToTargetIncludingScale, "SOC_BladeSheathe");
}

void AMain::UnsheatheBlade()
{
	// Attach blade to hand socket
	if (SpawnedBlade == nullptr) { return; }
	SpawnedBlade->AttachToComponent(GetMesh(), FAttachmentTransformRules::SnapToTargetIncludingScale, "SOC_Blade");
}

void AMain::Attack()
{
	if (SpawnedBlade == nullptr) { return; }
	UAnimMontage* AnimToPlay = SpawnedBlade->GetAttackAnimation(ComboIterator);

	if (AnimToPlay == nullptr) {
		ComboIterator = 0;
		AnimToPlay = SpawnedBlade->GetAttackAnimation(ComboIterator);
	}
	
	if (!CanAttack) { return; }
	UnsheatheBlade();

	if (GetCharacterMovement()->IsFalling()) {
		// TODO: Air combos
		return;
	}

	float AnimTime = PlayAnimMontage(AnimToPlay, 1.f);
	CanAttack = false;
	IsGroundAttacking = true;
	GetWorldTimerManager().SetTimer(TimerHandle, this, &AMain::ResetAttack, AnimTime, false);
}

void AMain::ResetAttack()
{
	ComboIterator = 0;
	CanAttack = true;
	IsGroundAttacking = false;
	SheatheBlade();
}

void AMain::IterateAttack()
{
	CanAttack = true;
	++ComboIterator;
}

