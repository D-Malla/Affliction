// Fill out your copyright notice in the Description page of Project Settings.


#include "MainPlayer.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
AMainPlayer::AMainPlayer()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Instantiating class components
	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("Spring Arm"));
	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));

	// Attaching SpringArm/Camera components to Root
	SpringArm->SetupAttachment(RootComponent);
	Camera->SetupAttachment(SpringArm);

	// Set default player variables
	PlayerHealth = 1.f;
	bHasPunched = false;
}

// Called when the game starts or when spawned
void AMainPlayer::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AMainPlayer::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AMainPlayer::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	// Player movment input
	PlayerInputComponent->BindAxis(TEXT("MoveForward"), this, &AMainPlayer::MoveForward);
	PlayerInputComponent->BindAxis(TEXT("MoveRight"), this, &AMainPlayer::MoveRight);
	PlayerInputComponent->BindAxis(TEXT("Turn"), this, &APawn::AddControllerYawInput);
	PlayerInputComponent->BindAxis(TEXT("LookUp"), this, &APawn::AddControllerPitchInput);
	PlayerInputComponent->BindAction(TEXT("Jump"), IE_Pressed, this, &ACharacter::Jump);
	PlayerInputComponent->BindAction(TEXT("Jump"), IE_Released, this, &ACharacter::StopJumping);
	PlayerInputComponent->BindAction(TEXT("Crouch"), IE_Pressed, this, &AMainPlayer::BeginCrouch);
	PlayerInputComponent->BindAction(TEXT("Crouch"), IE_Released, this, &AMainPlayer::EndCrouch);
	PlayerInputComponent->BindAction(TEXT("Sprint"), IE_Pressed, this, &AMainPlayer::BeginSprint);
	PlayerInputComponent->BindAction(TEXT("Sprint"), IE_Released, this, &AMainPlayer::EndSprint);

	// Damage/healing input
	PlayerInputComponent->BindAction(TEXT("Heal"), IE_Pressed, this, &AMainPlayer::StartHealing);
	PlayerInputComponent->BindAction(TEXT("Damage"), IE_Pressed, this, &AMainPlayer::StartDamage);

	// Melee input
	PlayerInputComponent->BindAction(TEXT("Melee"), IE_Pressed, this, &AMainPlayer::Melee);
}

void AMainPlayer::MoveForward(float AxisValue) 
{
	if ((Controller != nullptr) && (AxisValue != 0.f))
	{
		// Get forward rotation
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0.f, Rotation.Yaw, 0.f);

		// Get forward vector
		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
		AddMovementInput(Direction, AxisValue);
	}
}

void AMainPlayer::MoveRight(float AxisValue) 
{
		if ((Controller != nullptr) && (AxisValue != 0.f))
	{
		// Get right rotation
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0.f, Rotation.Yaw, 0.f);

		// Get right Vector
		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

		// Add movement in that direction
		AddMovementInput(Direction, AxisValue);
	}
}

void AMainPlayer::BeginSprint() 
{
	GetCharacterMovement()->MaxWalkSpeed = 1000.f;
}

void AMainPlayer::EndSprint() 
{
	GetCharacterMovement()->MaxWalkSpeed = 600.f;
}

void AMainPlayer::BeginCrouch()
{
  Crouch();
}

void AMainPlayer::EndCrouch()
{
  UnCrouch();
	GetCharacterMovement()->GetNavAgentPropertiesRef().bCanCrouch = true;
}

// Healing/Damage

void AMainPlayer::StartDamage() 
{
	TakeDamage(0.25f);
}

void AMainPlayer::TakeDamage(float DamageAmount) 
{
	UE_LOG(LogTemp, Warning, TEXT("We are taking Damage for %f points."), DamageAmount);
	PlayerHealth -= DamageAmount;

	if (PlayerHealth < 0.f)
	{
		PlayerHealth = 0.f;
	}
	UE_LOG(LogTemp, Warning, TEXT("Health: %f"), PlayerHealth);
}

void AMainPlayer::StartHealing() 
{
	Heal(0.25f);
}

void AMainPlayer::Heal(float HealAmount) 
{
	UE_LOG(LogTemp, Warning, TEXT("We are Healing for %f points."), HealAmount);
	PlayerHealth += HealAmount;

	if (PlayerHealth > 1.f)
	{
		PlayerHealth = 1.f;
	}
	UE_LOG(LogTemp, Warning, TEXT("Health: %f"), PlayerHealth);
}

void AMainPlayer::Melee()
{
	bHasPunched = true;
}