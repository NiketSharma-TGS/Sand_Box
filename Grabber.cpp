
#include "Grabber.h"
#include "Components/AudioComponent.h"
#include "DrawDebugHelpers.h"
#include "Engine/World.h"
#include "GameFramework/PlayerController.h"
#include "PhysicsEngine/PhysicsHandleComponent.h"

#define OUT


UGrabber::UGrabber()
{
	PrimaryComponentTick.bCanEverTick = true;
}


void UGrabber::BeginPlay() 
{
	Super::BeginPlay();

	FindPhysicsHandle();
	
	SetupInputComponent();

	FindAudioComponent();

}


//Checks for Physics Handle Component
void UGrabber::FindPhysicsHandle()
{
	PhysicsHandle = GetOwner()->FindComponentByClass<UPhysicsHandleComponent>();
	if (!PhysicsHandle)
	{
		//If the actor doesn't have a physics handle then a null ptr is received, this is a failsafe for that
		//Physics Handle found
		UE_LOG(LogTemp, Warning, TEXT("Physics Handle component is not present in %s"), *GetOwner()->GetName());
	}
}

//Checks for an input component
void UGrabber::SetupInputComponent()
{
	InputComponent = GetOwner()->FindComponentByClass<UInputComponent>();

	if (InputComponent)
	{
		InputComponent->BindAction("Grab", IE_Pressed, this, &UGrabber::Grab);  //here &gets the adress to Grab, it is not getting called but being told where to go.
		InputComponent->BindAction("Grab", IE_Released, this, &UGrabber::Release);
																			  
	}
	
	/*else
	{
		UE_LOG(LogTemp, Warning, TEXT("Input component is not present in %s"), *GetOwner()->GetName());
	} */

}

void UGrabber::FindAudioComponent()
{
	AudioComponent = GetOwner()->FindComponentByClass<UAudioComponent>();

	if (!AudioComponent)
	{
		UE_LOG(LogTemp, Error, TEXT("No Audio component found"));
	}

}

void UGrabber::Grab()
{
	//Grab is called in SetInputComponent()
	
	GetPlayersViewport();
	AudioComponent->Play();
	
	UE_LOG(LogTemp, Warning, TEXT("Grabber Pressed"));

	//Ray-cast only when the key is presse and reseacrh any actors with Physics body coliision channel set

	FHitResult HitResult = GetFirstPhysicsBodyInReach();
	UPrimitiveComponent* ComponentToGrab = HitResult.GetComponent();
	AActor* ActorHit = HitResult.GetActor(); //to be used in If below
	// If we hit something then attach the physics channel

	if (ActorHit)
	{ 
		if (!PhysicsHandle) { return;}        //This will exit out of the if statement when no PhysicsHandle is present. Protecting the code down below.
		
		PhysicsHandle->GrabComponentAtLocation
		(
		ComponentToGrab,
		NAME_None,
		LineTraceEnd
		);
	}
}

void UGrabber::Release()
{
	UE_LOG(LogTemp, Warning, TEXT("Grabber Released"));
	if (!PhysicsHandle) { return;} //Same as in Grab() 
	PhysicsHandle->ReleaseComponent();
	//Releases  the physics handle
}


// Called every frame
void UGrabber::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	

	//if the Phys handle is attached, move the objects we are holding
	if (!PhysicsHandle) { return; }
	if (PhysicsHandle->GrabbedComponent)
	{
		GetPlayersViewport();
		PhysicsHandle->SetTargetLocation(LineTraceEnd);
	}
	
}


FHitResult UGrabber::GetFirstPhysicsBodyInReach() 
{
	GetPlayersViewport(); 
	
	//Direction from FRotation to a Unit vector
	//DebugLine(PV_Location, LineTraceEnd);
	//Ray-cast to a certain distance(Reach)
	
	
	FHitResult Hit;
	FCollisionQueryParams TraceParams(FName(TEXT("")), false, GetOwner());

	GetWorld()->LineTraceSingleByObjectType(
		OUT Hit,
		PV_Location,
		LineTraceEnd,
		FCollisionObjectQueryParams(ECollisionChannel::ECC_PhysicsBody),
		TraceParams
	);

	return Hit;
}

void UGrabber::GetPlayersViewport() 
{
	//Getting players viewport-
	GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(
		OUT PV_Location,
		OUT PV_Rotation
	);

	FVector LineTraceDirection = PV_Rotation.Vector();
	LineTraceEnd = PV_Location + (LineTraceDirection * Reach);
}

//void UGrabber::DebugLine(FVector PV_Location_L, FVector LineTraceEnd_L)
//{
//	
//	
//	DrawDebugLine(
//		GetWorld(),
//		PV_Location_L,		//Start point is Players Location
//		LineTraceEnd_L,		//End is at the lenght of reach and direction of players view
//		FColor(0, 255, 0),
//		false,
//		0.f,				//For Lifetime ()in float)
//		0,					//Uint8 = integer value
//		5.f					//Width in pixels
//	);
//
//}