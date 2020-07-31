// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CameraDirector.generated.h"

UCLASS()
class MYPROJECT_API ACameraDirector : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ACameraDirector();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// The UPROPERTY macro makes our variables visible to the Unreal Engine 
	// This way, values set in these variables will not be reset when we launch the game or reload 
	// our level or project in a future work session.

	// We have also added the EditAnywhere keyword, which will allow us to set CameraOne and CameraTwo in the Unreal Editor 
	UPROPERTY(EditAnywhere, Category = "CameraDirector")
		AActor* CameraOne;

	UPROPERTY(EditAnywhere, Category = "CameraDirector")
		AActor* CameraTwo;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CameraDirector")
		float TimeToNextCameraChange;

};