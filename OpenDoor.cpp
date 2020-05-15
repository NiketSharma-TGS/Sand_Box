// Fill out your copyright notice in the Description page of Project Settings.


#include "GameFramework/PlayerController.h"
#include "Engine/World.h"
#include "OpenDoor.h"
#include "GameFramework/Actor.h" 

// Sets default values for this component's properties
UOpenDoor::UOpenDoor()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;


}

/* Use 2 functions instead if you want different speeds when closing and opening door, or if/else in Tick will need to be get
more complicated. In placed where you just want to use only close or open. This will be a problem. so switch to 2 functions in the future*/

void UOpenDoor::BeginPlay()
{
	Super::BeginPlay();	
	InitialYaw = GetOwner()->GetActorRotation().Yaw;
	CurrentYaw = InitialYaw;
	TargetYaw +=InitialYaw;    //Target Yaw is an Exposed Parameter in the Engine. Value set in Headerfile + Engine default
	//OpenYaw = TargetYaw;     // alt version
							   //This sets up the FinalTarget for use in UE. 
	
	FString ActorName = GetOwner()->GetName();
	if (!PressurePlate)
	{
		UE_LOG(LogTemp, Error, TEXT("%s has the Open Door component but no PressurePlate set"), *ActorName);
	}

	ActorThatOpens = GetWorld()->GetFirstPlayerController()->GetPawn();  //Sets the player pawn to the ActorThatOpens
}


// Called every frame
void UOpenDoor::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{	
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	//FRotator CurrentRotation = GetOwner()->GetActorRotation();
	if (PressurePlate && PressurePlate->IsOverlappingActor(ActorThatOpens))  //For Opening //Replace IsOverlapping with a function to calculate total mass in the volume
	{
		//TargetYaw = OpenYaw;
		OpenDoor(DeltaTime);
		DoorLastOpen = GetWorld()->GetTimeSeconds(); 
	}

	else //For closing
	{
		
		if (GetWorld()->GetTimeSeconds() - DoorLastOpen > DoorCloseDelay)
		{
			CloseDoor(DeltaTime);
		}
				
		
		
	
	}

}
/* In alt. version, explicitly check for T/F in both if and else otherwise plain else fails, ==True/==False, 
	Couldv'e kept everything Yaw for values just replaced the end input to to a new Roll var*/

void UOpenDoor::OpenDoor(float DTime)
{
	//Code to open the door
	//CurrentYaw = GetOwner()->GetActorRotation().Yaw;             //CurrentYaw should be set here and totally not on BeginPlay(). Values will change all the time during gameplay if more functionalaties are added to doors
	UE_LOG(LogTemp, Warning, TEXT("Yaw value: %f"), CurrentYaw);	//float CurrentYaw = CurrentRotation.Yaw;
	FRotator UpdateRotation;
	CurrentYaw = FMath::Lerp(CurrentYaw, TargetYaw, DTime*DoorOpenSpeed);     //Fx. for Linear Interpolation, TargetYaw is initialised in .h, Private
	UpdateRotation.Yaw = CurrentYaw;
	GetOwner()->SetActorRotation(UpdateRotation);

	
}


void UOpenDoor::CloseDoor(float DTime)		
{ 
	FRotator UpdateRotation;
	CurrentYaw = FMath::Lerp(CurrentYaw, InitialYaw, DTime*DoorCloseSpeed);     
	UpdateRotation.Yaw = CurrentYaw;
	GetOwner()->SetActorRotation(UpdateRotation);

}
	/*You will need to chane stupid else in Tick() and make it call CloseDoor
	Un-Comment CloseDOor declaration in .h and remove OpenYaw stuff.
	Current yaw updation in Open door. 
	Also OpenYaw will be useless then. use deltatime*float val. to modify the speeds
	This is form inside of tick comp.-
	TargetYaw = InitialYaw; //This will work for closing if the InitalYaw is set at the closed door
	For alt. program: Open door can close if TargetYaw is changed to the closed state angle
	*/

