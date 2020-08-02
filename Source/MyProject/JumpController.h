// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "JumpController.generated.h"

/**
 * 
 */
UCLASS()
class MYPROJECT_API AJumpController : public APlayerController
{
	GENERATED_BODY()

public: 
	virtual void BeginPlay() override; 
};
