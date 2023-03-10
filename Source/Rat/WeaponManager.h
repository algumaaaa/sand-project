// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/StaticMeshComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Animation/AnimMontage.h"
#include "WeaponManager.generated.h"


UCLASS()
class RAT_API AWeaponManager : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AWeaponManager();
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Mesh")
	UStaticMeshComponent* WeaponMesh;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Socket")
	FName EquipSocket;
	UPROPERTY(BlueprintReadWrite, Category = "Animation")
	TArray<UAnimMontage*> AttackA;
	UPROPERTY(BlueprintReadWrite, Category = "Animation")
	TArray<UAnimMontage*> AttackB;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	UAnimMontage* GetAttackAnimation(int Value);
};
