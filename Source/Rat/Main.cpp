
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