// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GameFramework/RotatingMovementComponent.h"
#include "ACollectible.generated.h"

UCLASS()
class MYPROJECT_API AACollectible : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AACollectible();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Static Mesh component 
	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* SM;

	// Just a simple but fancy rotation
	UPROPERTY(VisibleAnywhere)
	URotatingMovementComponent* RotatingComp;

	// The function that fires when we have an overlap 
	UFUNCTION()
	void Overlap(AActor* OverlappedActor, AActor* OtherActor);
};
