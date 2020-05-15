// Fill out your copyright notice in the Description page of Project Settings.
//This cpp mainly focuses on the dev. of Opening a door mechanism. Exposing a param to the engine
//so, The max value for a door to open can be set in the engine in the respective component settings

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Engine/TriggerVolume.h"
#include "OpenDoor.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class ESHCAPE_API UOpenDoor : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UOpenDoor();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;


private:
	void OpenDoor(float DTime);
	void CloseDoor(float Dtime);

	
	float InitialYaw;
	float CurrentYaw;
	//float OpenYaw;    //for alt. version
	
	UPROPERTY(EditAnywhere) //Yaw for the target, how much door should open, can be set in the engine.
	float TargetYaw = 90.f;

	
	UPROPERTY(EditAnywhere)
	ATriggerVolume* PressurePlate;

	UPROPERTY(EditAnywhere)
	AActor* ActorThatOpens;

	UPROPERTY(EditAnywhere)
	float DoorOpenSpeed = .5f;

	UPROPERTY(EditAnywhere)
	float DoorCloseSpeed = 1.2f;

	float DoorLastOpen = 0.f;

	UPROPERTY(EditAnywhere)
	float DoorCloseDelay = 1.f;  //Tune the time for playability 
	
	
};
