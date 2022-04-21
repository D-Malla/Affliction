// Fill out your copyright notice in the Description page of Project Settings.


#include "HealthPotion.h"
#include "Affliction/Game/Health/HealthComponent.h"

AHealthPotion::AHealthPotion()
{

}

void AHealthPotion::DrinkPotion(UHealthComponent* HealthComponent) 
{
  if (!HealthComponent)
  {
    UE_LOG(LogTemp, Warning, TEXT("No HealthComponent!!!!!!!!!"))
    return;
  }
  

  if(HealthComponent->Health < 100.f)
  {
    HealthComponent->Health += HealAmount;
  }
}
