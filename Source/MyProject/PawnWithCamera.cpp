// Fill out your copyright notice in the Description page of Project Settings.


#include "PawnWithCamera.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"

// Sets default values
APawnWithCamera::APawnWithCamera()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// This creates a basic, empty SceneComponent as the root of our Component hierarchy, then creates and attached a SpringArmComponent to it. 
	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent"));
	OurCameraSpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraSpringArm"));
	OurCameraSpringArm->SetupAttachment(RootComponent);
	
	// The Spring Arm is then set at a default pitch of -60 degrees (that is, looking 60 degrees downward) and a position of 50 units about the root. 
	OurCameraSpringArm->SetRelativeLocationAndRotation(FVector(0.0f, 0.0f, 50.0f), FRotator(-00.0, 0.0f, 0.0f));
	
	// We also established a few values specific to the SpringArmComponent clas that will determine its length and smoothness of motion
	OurCameraSpringArm->TargetArmLength = 400.0f;
	OurCameraSpringArm->bEnableCameraLag = true; 
	OurCameraSpringArm->CameraLagSpeed = 3.0f;

	// Create and attach a CameraComponent to the socket on the end of SpringArmComponent 
	OurCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("GameCamera"));
	OurCamera->SetupAttachment(OurCameraSpringArm, USpringArmComponent::SocketName);

	// Take control of the default player 
	AutoPossessPlayer = EAutoReceiveInput::Player0;

}

// Called when the game starts or when spawned
void APawnWithCamera::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void APawnWithCamera::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	// Zoom in if ZoomInButton is down, zoom back out if it's not 
	{
		if (bZoomingIn)
		{
			ZoomFactor += DeltaTime / 0.5f;	// Zoom in over half a second 
		}

		else
		{
			ZoomFactor -= DeltaTime / 0.25f;	// Zoom out over a quarter of a second
		}

		ZoomFactor = FMath::Clamp<float>(ZoomFactor, 0.0f, 1.0f);

		// Blend our camera's FOV and our SpringArm's length based on Zoom Factor 
		OurCamera->FieldOfView = FMath::Lerp<float>(90.0f, 60.0f, ZoomFactor);
		OurCameraSpringArm->TargetArmLength = FMath::Lerp<float>(400.0f, 300.0f, ZoomFactor);
	}

	// This code uses several hard coded values, like the half-second and quarter-second zoom times,
	// the 90-degree zoomed-out and 60-degree zoomed-in field of view values, 
	// and the 400 zoomed-out and 300 zoomed-in camera distances 
	// Values like this should generally be exposed to the editor as vairbales tagged with the UPROPERTY(EditAnywher)
	// so that non-programmers can change them, or so that programmers can change them withou recompiling code,
	// or even while playing the game in the editor 


	// This block of code rotates our Pawn's yaw direclty with the mouse's X axis, 
	// but only the camera system responds to the pitch changes from the mouse's Y axis.
	// Rotating any Actor or Actor subclass rotates the root-level Component,
	// which indirectly affects everthing attatched to it. 

	// Rotate the actor's yaw, which will turn our camera because we're attatched to it 
	{
		FRotator NewRotation = GetActorRotation();
		NewRotation.Yaw += CameraInput.X;
		SetActorRotation(NewRotation);
	}

	// Rotate our camera's pitch, but limit it so we're always looking downward
	
	
	{
		FRotator NewRotation = OurCameraSpringArm->GetComponentRotation();
		NewRotation.Pitch = FMath::Clamp(NewRotation.Pitch + CameraInput.Y, -80.0f, -15.0f);
		OurCameraSpringArm->SetWorldRotation(NewRotation);
	}


	// Using GetActorForwardVector and GetActorRightVector allows us to move relative to the direction the actor is facing 
	// Since the camera faces the same way as the actor, this ensures that our forward key is always relative to what the player sees. 

	
	// Handle movement based on "MoveX" and "MoveY" axes 
	{
		if (!MovementInput.IsZero())
		{
			// Scale our movement input axis values by 100 units per second
			MovementInput = MovementInput.GetSafeNormal() * 100.0f;
			FVector NewLocation = GetActorLocation();
			NewLocation += GetActorForwardVector() * MovementInput.X * DeltaTime;
			NewLocation += GetActorRightVector() * MovementInput.Y * DeltaTime;
			SetActorLocation(NewLocation);
		}
	}
	
}

// Called to bind functionality to input
void APawnWithCamera::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	// Hook up events for "ZoomIn"
	PlayerInputComponent->BindAction("ZoomIn", IE_Pressed, this, &APawnWithCamera::ZoomIn);
	PlayerInputComponent->BindAction("ZoomIn", IE_Released, this, &APawnWithCamera::ZoomOut);

	// Hook up every-frame handling of our four axes 
	PlayerInputComponent->BindAxis("MoveForward", this, &APawnWithCamera::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &APawnWithCamera::MoveRight);
	PlayerInputComponent->BindAxis("LookUp", this, &APawnWithCamera::PitchCamera);
	PlayerInputComponent->BindAxis("Turn", this, &APawnWithCamera::YawCamera);

}

// Input functions 
void APawnWithCamera::MoveForward(float AxisValue)
{
	MovementInput.X = FMath::Clamp<float>(AxisValue, -1.0, 1.0f);
}

void APawnWithCamera::MoveRight(float AxisValue)
{
	MovementInput.Y = FMath::Clamp<float>(AxisValue, -1.0, 1.0f);
}

void APawnWithCamera::PitchCamera(float AxisValue)
{
	CameraInput.Y = AxisValue;
}

void APawnWithCamera::YawCamera(float AxisValue)
{
	CameraInput.X = AxisValue;
}

void APawnWithCamera::ZoomIn()
{
	bZoomingIn = true;
}

void APawnWithCamera::ZoomOut()
{
	bZoomingIn = false;
}