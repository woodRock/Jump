// Fill out your copyright notice in the Description page of Project Settings.


#include "JumpController.h"

void AJumpController::BeginPlay()
{
	Super::BeginPlay();
	SetInputMode(FInputModeGameAndUI());
}

