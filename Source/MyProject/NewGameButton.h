// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "WidgetBlueprint.h"
#include "NewGameButton.generated.h"

/**
 * 
 */
UCLASS(Blueprintable)
class MYPROJECT_API UNewGameButton : public UWidgetBlueprint
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "FloatingActor")
	float FloatSpeed = 20.0f;
	
	
};
