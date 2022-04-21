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

	PlayerInputComponent->BindAxis("MoveForward",this, &AMainPlayer::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &AMainPlayer::MoveRight);
	PlayerInputComponent->BindAxis("Turn", this, &APawn::AddControllerYawInput);
	PlayerInputComponent->BindAxis("LookUp", this, &APawn::AddControllerPitchInput);
	PlayerInputComponent->BindAction("Jump",IE_Pressed,this, &ACharacter::Jump);
	PlayerInputComponent->BindAction("Jump",IE_Released,this, &ACharacter::StopJumping);
	PlayerInputComponent->BindAction("Crouch",IE_Pressed,this,&AMainPlayer::BeginCrouch);
	PlayerInputComponent->BindAction("Crouch",IE_Released,this,&AMainPlayer::EndCrouch);
	PlayerInputComponent->BindAction("Sprint",IE_Pressed,this, &AMainPlayer::BeginSprint);
	PlayerInputComponent->BindAction("Sprint",IE_Released,this, &AMainPlayer::EndSprint);
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