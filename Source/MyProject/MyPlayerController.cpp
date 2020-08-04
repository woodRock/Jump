// Fill out your copyright notice in the Description page of Project Settings.


#include "MyPlayerController.h"
#include "JumpCharacter.h"

void AMyPlayerController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);
	if (CollectiblesWidgetBP)
	{
		// Creating our widget and adding it to our viewport 
		CollectiblesWidget = CreateWidget<UCollectiblesUI>(this, CollectiblesWidgetBP);
		CollectiblesWidget->AddToViewport();
	}
}

void AMyPlayerController::UpdateCollectedItems(FText ItemName)
{
	Char = Cast<AJumpCharacter>(GetPawn());
	if (Char)
	{
		// Updating our UI with the new collected item 
		CollectiblesWidget->AddItemToUI(ItemName);
	}
}