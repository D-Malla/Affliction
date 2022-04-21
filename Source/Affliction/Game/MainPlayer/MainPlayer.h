// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "MainPlayer.generated.h"

class UCameraComponent;
class USpringArmComponent;

UCLASS()
class AFFLICTION_API AMainPlayer : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AMainPlayer();

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Definite Components
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Components")
	USpringArmComponent* SpringArm;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Components")
	UCameraComponent* Camera;

private:

	// Forwards/backwards movement
	void MoveForward(float AxisValue);

	// Left/Right movement
	void MoveRight(float AxisValue);

	// Sets character movement Speed to Sprint values
	void BeginSprint();

	// Sets character movement Speed back to default Speed values
	void EndSprint();

	// Crouch functions
	void BeginCrouch();
	void EndCrouch();
};
