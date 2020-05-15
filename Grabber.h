// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "PhysicsEngine/PhysicsHandleComponent.h"
#include "Grabber.generated.h"



UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class SANDBOX1_API UGrabber : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UGrabber();

	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;


protected:
	// Called when the game starts 
	virtual void BeginPlay() override;
	

private:
	//Reach variable decides the users grab reach
	float Reach = 100.f;
	FVector PV_Location;
	FRotator PV_Rotation;
	FVector LineTraceEnd;

	UPROPERTY()
	UPhysicsHandleComponent* PhysicsHandle = nullptr;
	UPROPERTY()									//Anythin with U should have URPOPERTY()
	UInputComponent* InputComponent = nullptr;
	UPROPERTY()
	UAudioComponent* AudioComponent = nullptr;

	void Grab();
	void Release();
	void FindPhysicsHandle();
	void SetupInputComponent();
	void FindAudioComponent();
	void GetPlayersViewport();
	
	//void DebugLine(FVector PV_Location_L, FVector LineTraceEnd_L);

	// Returns the first Phys body Actor within reach
	FHitResult GetFirstPhysicsBodyInReach();

	
};



