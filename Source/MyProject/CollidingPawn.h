// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "CollidingPawnMovementComponent.h"
#include "CollidingPawn.generated.h"

UCLASS()
class MYPROJECT_API ACollidingPawn : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ACollidingPawn();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	//	Called every frame
	virtual void Tick(float DeltaTime) override;

	//	Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	//	This variable keeps track of a Particle System Component that we will create later.
	//	We can create components without making variables to track them,
	//	but is we want to use those components in our code, we should shtore them in class member variables
	UPROPERTY()
	class UParticleSystemComponent* OurParticleSystem;

	//	In order to use our custom Pawn Movement Component, we will first need to add a variable to our pawn class to keep track of it. 
	UPROPERTY()
	class UCollidingPawnMovementComponent* OurMovementComponent;

	// Pawns have a function called GetMovementComponent that is used to enable other classes in the engine to access the Pawn Movement Compontnet that the Pawn is currently using.
	// We will need to override that function so that it returns our custom Pawn Movement component.
	virtual UPawnMovementComponent* GetMovementComponent() const override;

	
	// With our new Pawn Movement Component setup, we can create code to handle the input that our Pawn will recieve 
	// We start by declaring a few functions in our class definition
	void MoveForward(float AxisValue);

	void MoveRight(float AxisValue);

	void Turn(float AxisValue);

	void ParticleToggle();

};
