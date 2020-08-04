// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Internationalization/Text.h"
#include "CollectiblesUI.generated.h"

/**
 * 
 */
UCLASS()
class MYPROJECT_API UCollectiblesUI : public UUserWidget
{
	GENERATED_BODY()

protected:
	// Responsible for adding the ItemToAdd for our UI
	UFUNCTION(BlueprintImplementableEvent, Category = UI)
	void AddItemToUI();

	// The enxt item that is going to get added inside our UI 
	UPROPERTY(BlueprintReadOnly)
	FText ItemToAdd;

public:
	// Adds the name of the item we collected inside our UI by using our AddItemToUI protected function 
	void AddItemToUI(FText ItemName);
};
