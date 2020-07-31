// Fill out your copyright notice in the Description page of Project Settings.


#include "CollidingPawnMovementComponent.h"

void UCollidingPawnMovementComponent::TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// Make sure everything is still valid, and that we are allowed to move here 
	if (!PawnOwner || !UpdatedComponent || ShouldSkipUpdate(DeltaTime))
	{
		return;
	}

	// Get (and then clear) the movement vector that we set in ACollidingPawn::Tick 
	FVector DesiredMovementThisFrame = ConsumeInputVector().GetClampedToMaxSize(1.0f) * DeltaTime * 150.0f; 

	if (!DesiredMovementThisFrame.IsNearlyZero())
	{
		FHitResult Hit;
		SafeMoveUpdatedComponent(DesiredMovementThisFrame, UpdatedComponent->GetComponentRotation(), true, Hit);

		// If we bumbed into something, try to slide a long it 
		if (Hit.IsValidBlockingHit())
		{
			// This code will move our Pawn smoothly around the world, sliding off of surfaces where appropriate.
			// There is no gravity applied to our Pawn, and its maximum speed is hard-coded to 150 Unreal Units per second 
			SlideAlongSurface(DesiredMovementThisFrame, 1.f - Hit.Time, Hit.Normal, Hit);
		}
	}
}

//	NOTE 
//	This TickComponent function makes use of a few of the powerful features offered by the UPawnMovementComponent class:
//		-	ConsumeInputVector reports and clears the value of a build-in variable that we will use to store our movement inputs 
//		-	SafeMoveUpdatedComponent uses Unreal Engine physics to move our pawn Movement Component while respecting solid barriers 
//		-	SlideAlongSurface handles the calculations and physics involved with sliding smoothly along collision surfaces like walls and ramps when a move results in a collision, 
//			rather than simply stopping in place and sticking to the wall or ramp 
