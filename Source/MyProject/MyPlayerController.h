// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "CollectiblesUI.h"
#include "MyPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class MYPROJECT_API AMyPlayerController : public APlayerController
{
	GENERATED_BODY()

private:
	// Our UI reference
	UCollectiblesUI* CollectiblesWidget;

protected:
	// Property which is pointing to out Widget Bluepring in order to instantiate it using C++ 
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UCollectiblesUI> CollectiblesWidgetBP;

public:
	// The character for the controller to control
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Character")
	ACharacter* Char;

	// Executes when the controller possess a pawn 
	virtual void OnPossess(APawn* InPawn) override;

	// Updates the UI base don the item that the player has collected
	void UpdateCollectedItems(FText ItemName);
};
