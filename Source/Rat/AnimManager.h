// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "AnimManager.generated.h"

UCLASS(Transient, Blueprintable, HideCategories=AnimInstance, BlueprintType)
class RAT_API UAnimManager : public UAnimInstance
{
	GENERATED_BODY()
public:
	UAnimManager();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "General")
	float Speed;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "General")
	bool IsInAir;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "General")
	float VerticalSpeed;

	virtual void NativeUpdateAnimation(float DeltaSeconds) override;
	void AnimNotify_IterateCombo();
	
};
