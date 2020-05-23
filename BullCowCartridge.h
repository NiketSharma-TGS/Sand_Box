// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Console/Cartridge.h"
#include "BullCowCartridge.generated.h"

struct FBullCowCount
{
	int32 Bulls = 0;      // They can be left un-initalized and assign them when we instantiate the struct later
	int32 Cows = 0;
};


UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class BULLCOWGAME_API UBullCowCartridge : public UCartridge
{
	GENERATED_BODY()

public:
	virtual void BeginPlay() override;
	virtual void OnInput(const FString& Input) override;
	void SetupGame();
	void GameOver();
	void GuessProcessor(FString Guess);
	bool IsIsogram(const FString& WordL) const;    //This function doesn't make any changes to any non const member of the class
	const FString WordListChecker(TArray<FString> WordList) const; //Not making changes to the collection being used so it is constant
	FBullCowCount BullsNCows(FString Guess) const;

	
private:
	FString HiddenWord; //Just declare stuff here to be used globally and by globally I mean in UBullCowCartridge
	FString GuessWord;
	int32 WordLength;
	int32 Lives;
	bool bGameOver;

};
 