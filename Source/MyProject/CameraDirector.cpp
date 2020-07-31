// Fill out your copyright notice in the Description page of Project Settings.


#include "CameraDirector.h"

//	The GameplayStatics header file gives us access to some useful general-purpose functions
#include "Kismet/GameplayStatics.h"

// Sets default values
ACameraDirector::ACameraDirector()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ACameraDirector::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ACameraDirector::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	const float TimeBetweenCameraChanges = 2.0f;
	const float SmoothBlendTime = 0.75f;
	TimeToNextCameraChange -= DeltaTime;
	
	if (TimeToNextCameraChange <= 0.0f)
	{
		TimeToNextCameraChange += TimeBetweenCameraChanges;

		//	Find the actor that hanldes control for the local players 
		APlayerController* OurPlayerController = UGameplayStatics::GetPlayerController(this, 0);

		if (OurPlayerController)
		{
			if ((OurPlayerController->GetViewTarget() != CameraOne) && (CameraOne != nullptr))
			{
				// Cust instantly to camera one. 
				OurPlayerController->SetViewTarget(CameraOne);
			}
			else if ((OurPlayerController->GetViewTarget() != CameraOne) && (CameraOne != nullptr))
			{
				//	Blend smoothly to camera two. 
				OurPlayerController->SetViewTargetWithBlend(CameraTwo, SmoothBlendTime);

			}
		} 
	}

}

