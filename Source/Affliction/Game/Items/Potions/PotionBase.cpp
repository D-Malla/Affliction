// Fill out your copyright notice in the Description page of Project Settings.


#include "PotionBase.h"
#include "Components/CapsuleComponent.h"


// Sets default values
APotionBase::APotionBase()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	// Instantiating class components
	Capsule = CreateDefaultSubobject<UCapsuleComponent>(TEXT("Capsule Component"));
	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Static Mesh"));

	// Attaching Collision/Static Mesh to RootComponent
	RootComponent = Capsule;
	StaticMesh->SetupAttachment(Capsule);

}

// Called when the game starts or when spawned
void APotionBase::BeginPlay()
{
	Super::BeginPlay();
	
}

