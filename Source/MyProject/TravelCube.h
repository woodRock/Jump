// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "TravelCube.generated.h"

UCLASS()
class MYPROJECT_API ATravelCube : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ATravelCube();

	// Makes this component visible in the Editor
	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* VisualMesh;

	// Can adjust the speed of the the platform from the editor
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="TravelCube")
	float FloatSpeed = 100.0f;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
