// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PawnMovementComponent.h"
#include "CollidingPawnMovementComponent.generated.h"

/**
 * 
 */
UCLASS()
class MYPROJECT_API UCollidingPawnMovementComponent : public UPawnMovementComponent
{
	GENERATED_BODY()

	// All we really need to write is a TickComponent function (similar to an Actor's Tick Function)
	// to tell us how to move each frame. We do this by overiding the TickComponent definition in the header file here 
	public:
		virtual void TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	
};
