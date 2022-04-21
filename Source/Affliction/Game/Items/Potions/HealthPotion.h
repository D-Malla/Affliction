// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PotionBase.h"
#include "HealthPotion.generated.h"

class UHealthComponent;

UCLASS()
class AFFLICTION_API AHealthPotion : public APotionBase
{
	GENERATED_BODY()
	
public:
	// Sets default values for this component's properties
	AHealthPotion();

	UHealthComponent* HealthComp;
	float HealAmount = 30.f;

	void DrinkPotion(UHealthComponent* HealthC);
};
