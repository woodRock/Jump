// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/TextRenderComponent.h"
#include "Countdown.generated.h"

UCLASS()
class MYPROJECT_API ACountdown : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ACountdown();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// How long, in seconds, the countdown will run
	UPROPERTY(EditAnywhere)
	int32 CountdownTime;

	UTextRenderComponent* CountdownText;
	void UpdateTimerDisplay();

	// Whenever we assign a Timer to run a function, we are given a Timer Handle.
	// We need to hold onto that handle so that we can shut the Timer down when the countdown finished.
	// This function is to count time down, and the Timer Handle we'll need to control it 
	void AdvanceTimer();

	UFUNCTION(BlueprintNativeEvent)
	void CountdownHasFinished();
	virtual void CountdownHasFinished_Implementation();
	
	FTimerHandle CountdownTimerHandle;
};
