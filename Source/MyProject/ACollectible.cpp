// Fill out your copyright notice in the Description page of Project Settings.


#include "ACollectible.h"
#include "JumpCharacter.h"

// Sets default values
AACollectible::AACollectible()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Creating our components
	SM = CreateDefaultSubobject<UStaticMeshComponent>(FName("SM"));
	RotatingComp = CreateDefaultSubobject<URotatingMovementComponent>(FName("RotatingMoveComp"));

}

// Called when the game starts or when spawned
void AACollectible::BeginPlay()
{
	Super::BeginPlay();

	// register the overlap function 
	OnActorBeginOverlap.AddDynamic(this, &AACollectible::Overlap);
	
}

// Called every frame
void AACollectible::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AACollectible::Overlap(AActor* OverlappedActor, AActor* OtherActor)
{
	Destroy();
}

