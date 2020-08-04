// Fill out your copyright notice in the Description page of Project Settings.


#include "JumpCharacter.h"
#include "MyPlayerController.h"

// Sets default values
AJumpCharacter::AJumpCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AJumpCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AJumpCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AJumpCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void AJumpCharacter::AddItemToUI(FText ItemName)
{
	AMyPlayerController* Con = Cast<AMyPlayerController>(GetController());
	if (Con) Con->UpdateCollectedItems(ItemName);
}

