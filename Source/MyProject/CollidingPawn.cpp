// Fill out your copyright notice in the Description page of Project Settings.


#include "CollidingPawn.h"

// We will create a Sphere component to interact with the physical world,
// a Static Mesh Component to represent our collision shape visually, 
// a Particle System Component that we can turn on or off at will 
// and a Spring Arm Component that we can use to attach a Camera Component to control our in-game perspective 
#include "UObject/ConstructorHelpers.h"
#include "particles/ParticleSystemComponent.h"
#include "Components/SphereComponent.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"

// Sets default values
ACollidingPawn::ACollidingPawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Decide which component will be the root of the hierarchy. 
	// We use the Sphere Component, since it is the physical presence that can interact and collide with our game world.
	// An Actor can have multiple physics-enabled Components in its hierarchy

	// Our root component will be a sphere that reacts to physics 
	USphereComponent* SphereComponent = CreateDefaultSubobject<USphereComponent>(TEXT("RootComponent"));
	RootComponent = SphereComponent;
	SphereComponent->InitSphereRadius(40.0f);
	SphereComponent->SetCollisionProfileName(TEXT("Pawn"));

	// Next, we will create and attach a visible sphere from a Static Mesh Asset that has a radius of 50 
	// Since this doesn't perfectly line up with the 40-radius Sphere Component we just created,
	// scale it down to 80%
	// We also need to move it down by 40 units in order to have its center line up with the center of the Sphere Component
	UStaticMeshComponent* SphereVisual = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("VisualRepresentation"));
	SphereVisual->SetupAttachment(RootComponent);

	// Hard-coding Asset paths, like the Static Meesh for the sphere in this example,
	// is not generally considered a best practise; \
	// we would usually create the Component in the constructor, make it editable,
	// then create a Blueprint Asset in the Unreal Editor and set  up the Static Mesh Asset there.
	// However it is possible to do this directly in code, and could be faster for programmer debugging or building new features
	static ConstructorHelpers::FObjectFinder<UStaticMesh> SphereVisualAsset(TEXT("/Game/StarterContent/Shapes/Shape_Sphere.Shape_Sphere"));
	if (SphereVisualAsset.Succeeded())
	{
		SphereVisual->SetStaticMesh(SphereVisualAsset.Object);
		SphereVisual->SetRelativeLocation(FVector(0.0f, 0.0f, -40.f));
		SphereVisual->SetWorldScale3D(FVector(0.8f));
	}

	// We can now attach an inactive Particle System Component to our hierarchy.
	// We can manipulate this Component in code, and later set up an input to turn it on of off 
	// Notice that the Particle System Component is attatched directly to the Static Mesh Component, not to the root.
	// It is also slightly offset from the bottom-center of the mesh so that it will be more visible during play. 

	// Create a particle system that we can activate or deactivate 
	OurParticleSystem = CreateDefaultSubobject <UParticleSystemComponent>(TEXT("MovementParticles"));
	OurParticleSystem->SetupAttachment(SphereVisual);
	OurParticleSystem->bAutoActivate = false;
	OurParticleSystem->SetRelativeLocation(FVector(-20.0, 0.0f, 20.0f));
	static ConstructorHelpers::FObjectFinder<UParticleSystem> ParticleAsset(TEXT("/Game/StarterContent/Particles/P_Fire.P_Fire"));
	if (ParticleAsset.Succeeded())
	{
		OurParticleSystem->SetTemplate(ParticleAsset.Object);
	}

	// A Spring Arm Component can provide a smoother attatchment point for our camera 
	// by allowing our camera to accelerate and decelerate more slowly than the Pawn it is following.
	// It also has a built-in feature that prevents the camera from going through solid objects,
	// for situations such as when a player backs into a corner in a third-person game.
	// While it isn't necessary, the Spring Arm Component can be very fast and easy way to get smoother camera work into a game 
	USpringArmComponent* SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraAttatchmentArm"));
	SpringArm->SetupAttachment(RootComponent);
	SpringArm->SetRelativeRotation(FRotator(-45.f, 0.f, 0.f));
	SpringArm->TargetArmLength = 400.0f;
	SpringArm->bEnableCameraLag = true;
	SpringArm->CameraLagSpeed = 3.0f;

	// The actual Camera Component is easy to create, and doesn't require any special settings for our case.
	// The Spring Arm Component has a special built-in socket that we can attach to, rather than attaching directly to the Component's base. 

	// Create a canera abd attach to our spring arm 
	UCameraComponent* Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Actual Camera"));
	Camera->SetupAttachment(SpringArm, USpringArmComponent::SocketName);

	// Now that our components are creates and attached, we should det this pawn to be controlled by the default player. 
	AutoPossessPlayer = EAutoReceiveInput::Player0;

	// Creating a Pawn Movement Component and associating it with our Pawn is simple 

	// Create an instace of our movement component, and tell it to update the root 
	OurMovementComponent = CreateDefaultSubobject<UCollidingPawnMovementComponent>(TEXT("CustomMovementComponent"));
	OurMovementComponent->UpdatedComponent = RootComponent;

	// NOTE
	// Unlike the other Components we've seen so far, we don't need to attach this Component to our own Component hierarchy.
	// This is because our other Components are all types of Scene Components, which inherent;y reuiqre physcial locations.
	// Movement Controllers, however, are not Scene Components and do not represent physical objects,
	// so the concept of existing at a physical location or being physically attached to another Component does not apply to them 
}

// Called when the game starts or when spawned
void ACollidingPawn::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ACollidingPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ACollidingPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	// Bind our functions to our input events 
	PlayerInputComponent->BindAction("ParticleToggle", IE_Pressed, this, &ACollidingPawn::ParticleToggle);
	PlayerInputComponent->BindAxis("MoveForward", this, &ACollidingPawn::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &ACollidingPawn::MoveRight);
	PlayerInputComponent->BindAxis("Trunb", this, &ACollidingPawn::Turn);
}

// We need to add the definition of our overridden function
UPawnMovementComponent* ACollidingPawn::GetMovementComponent() const
{
	return OurMovementComponent;
}

// We add the definitions of those functions 

void ACollidingPawn::MoveForward(float AxisValue)
{
	if (OurMovementComponent && (OurMovementComponent->UpdatedComponent == RootComponent))
	{
		OurMovementComponent->AddInputVector(GetActorForwardVector() * AxisValue);
	}
}


void ACollidingPawn::MoveRight(float AxisValue)
{
	if (OurMovementComponent && (OurMovementComponent->UpdatedComponent == RootComponent))
	{
		OurMovementComponent->AddInputVector(GetActorRightVector() * AxisValue);
	}
}

void ACollidingPawn::Turn(float AxisValue)
{
	FRotator NewRotation = GetActorRotation();
	NewRotation.Yaw = AxisValue;
	SetActorRotation(NewRotation);
}

void ACollidingPawn::ParticleToggle()
{
	if (OurParticleSystem && OurParticleSystem->Template) 
	{
		OurParticleSystem->ToggleActive();
	}
}



