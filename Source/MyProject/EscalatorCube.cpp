// Fill out your copyright notice in the Description page of Project Settings.


#include "EscalatorCube.h"

// Sets default values
AEscalatorCube::AEscalatorCube()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// The code we have added will fill our VisualMesh refernce in with a new StaticMeshComponent,
	// attach it to our Actor, and set it to the cube mesh from the Starter Content assets 
	VisualMesh = CreateAbstractDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	VisualMesh->SetupAttachment(RootComponent);
	static ConstructorHelpers::FObjectFinder<UStaticMesh> CubeVisualAsset(TEXT("/Game/StarterContent/Shapes/Shape_Cube.Shape_Cube"));
	if (CubeVisualAsset.Succeeded())
	{
		VisualMesh->SetStaticMesh(CubeVisualAsset.Object);
		VisualMesh->SetRelativeLocation(FVector(0.0f, 0.0f, 0.0f));
	}

}

// Called when the game starts or when spawned
void AEscalatorCube::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AEscalatorCube::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	// In this case, it will make our cube simultaneously rotate while also floating up and down.
	FVector NewLocation = GetActorLocation();
	float RunningTime = GetGameTimeSinceCreation();
	float DeltaHeight = (FMath::Sin(RunningTime + DeltaTime) - FMath::Sin(RunningTime));
	NewLocation.Z += DeltaHeight * EscalatorSpeed;
	SetActorLocation(NewLocation);

}

