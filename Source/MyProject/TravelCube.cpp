// Fill out your copyright notice in the Description page of Project Settings.


#include "TravelCube.h"

// Sets default values
ATravelCube::ATravelCube()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// The code we have added will fill our VisualMesh refernce in with a new StaticMeshComponent,
	// attach it to our Actor, and set it to the cube mesh from the Starter Content assets 
	VisualMesh = CreateAbstractDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	VisualMesh->SetupAttachment(RootComponent);
	static ConstructorHelpers::FObjectFinder<UStaticMesh> CubeVisualAsset(TEXT("/Game/StarterContent/Shapes/Shape_Cone.Shape_Cone"));
	if (CubeVisualAsset.Succeeded())
	{
		VisualMesh->SetStaticMesh(CubeVisualAsset.Object);
		VisualMesh->SetRelativeLocation(FVector(0.0f, 0.0f, 0.0f));
	}

	FRotator NewRotation = GetActorRotation();
	NewRotation.Yaw += 180.0f;
	SetActorRotation(NewRotation);
}

// Called when the game starts or when spawned
void ATravelCube::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ATravelCube::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	// In this case, it will make our cube simultaneously rotate while also floating up and down.
	FVector NewLocation = GetActorLocation();
	float RunningTime = GetGameTimeSinceCreation();
	float DeltaHeight = (FMath::Sin(RunningTime + DeltaTime) - FMath::Sin(RunningTime));
	NewLocation.X += DeltaHeight * FloatSpeed;
	SetActorLocation(NewLocation);
}

