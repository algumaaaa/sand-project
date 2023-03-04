// Fill out your copyright notice in the Description page of Project Settings.


#include "AnimManager.h"
#include "Main.h"
#include "GameFramework/CharacterMovementComponent.h"

UAnimManager::UAnimManager()
{
	Speed = 0.f;
	IsInAir = false;
	VerticalSpeed = 0.f;
}

void UAnimManager::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);

	AActor* OwningActor = GetOwningActor();
	if (OwningActor == nullptr) { return; }
	Speed = OwningActor->GetVelocity().Size();
	VerticalSpeed = OwningActor->GetVelocity().Z;

	AMain* OwningCharacter = Cast<AMain>(OwningActor);
	if (OwningCharacter == nullptr) { return; }
	IsInAir = OwningCharacter->GetCharacterMovement()->IsFalling();
}