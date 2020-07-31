// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "EscalatorCube.generated.h"

UCLASS()
class MYPROJECT_API AEscalatorCube : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AEscalatorCube();

	// This is the speed at which the platform elevates
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="EscalatorCube")
	float EscalatorSpeed = 200.0f;

	// Adds a static mesh to the Actor
	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* VisualMesh;


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
