// Fill out your copyright notice in the Description page of Project Settings.
#include "BullCowCartridge.h"
#include "HiddenWords.h"
#include "Math/UnrealMathUtility.h"   // To use RandRange. Found through UE Docs


void UBullCowCartridge::BeginPlay()  // When the game starts
{
    Super::BeginPlay();

	//int32 Number = 9;
	//FBullCowCount Count = {2, 3};      // Instantiating the Struct
	

	//FMath::RandRange(0, 10);  // Use later to generate random numbers
	
	PrintLine(TEXT("Welcome to Bulls & Cows"));
	SetupGame();


	//PrintLine(TEXT("The number of possible words is %i"), HiddenWords.Num());
	PrintLine(TEXT("The Word is %s: %i characters long"), *HiddenWord, WordLength); //Debug Line
	
	
	
	PrintLine(TEXT("Guess & Press Enter to Continue"));
	

	
}

void UBullCowCartridge::OnInput(const FString& Input)  //Input here is a reference 
{
	ClearScreen();
	
	PrintLine("Enter your guess");
	PrintLine(Input);
	GuessWord = Input;
	bool bIsogram = IsIsogram(GuessWord);
	if (bIsogram == false)
	{
		PrintLine(TEXT("Input is NOT an isogram"));
	}
	   
	FBullCowCount Score = BullsNCows(GuessWord);
	PrintLine(TEXT("BULLS: %i | COWS: %i"), Score.Bulls, Score.Cows);

	GuessProcessor(Input);
}

void UBullCowCartridge::SetupGame()
{
	HiddenWord = WordListChecker(HiddenWords);
	WordLength = HiddenWord.Len();
	Lives = HiddenWord.Len(); // Add if here to set lives according to Word Length

	PrintLine(TEXT("The word is %i characters long"), WordLength);
	PrintLine(TEXT("You have %i Lives"), Lives);
	PrintLine(TEXT("Type in your guess and Hit Enter"));


	
	//PrintLine(TEXT("Character 1 of the hidden word is: %c"), HiddenWord[0]);

	
}

const FString UBullCowCartridge::WordListChecker(TArray<FString> WordList) const  //Takes in the HiddenWords Collection, returns an FString for the Hidden Word
{
	TArray<FString> ValidWords;
	FString RandomHW;               //Word to be returned from the filtered collection

	for (FString WordFromList : WordList)
	{
		if ((WordFromList.Len() == 5) && (IsIsogram(WordFromList) == true))  // Filter for the Words
		{
			ValidWords.Emplace(WordFromList);                               //Creates a new collection from the filtered words
			continue;
		}

	}
	
	int32 RandomIndex = FMath::RandRange(0, ValidWords.Num());
	PrintLine(TEXT("Random number = %i"), RandomIndex);
	RandomHW = ValidWords[RandomIndex];
	
	return RandomHW;
}

void UBullCowCartridge::GameOver()
{

	PrintLine(TEXT("Thanks for Playing"));

}

void UBullCowCartridge::GuessProcessor(FString Guess)
{
	
	if (HiddenWord == Guess)
	{
		PrintLine(TEXT("You Won!"));
		GameOver();
		return;
	}

	else
	{
		--Lives;

		if (Guess.Len() == WordLength)
		{
			PrintLine(TEXT("Try Again!"));
			PrintLine(TEXT("\nLives Left %i"), Lives);
		}

		else
		{
			PrintLine(TEXT("Wrong Lenght"));
			PrintLine(TEXT("\nLives Left %i"), Lives);
		}

	}


	if (Lives == 0)
	{
		PrintLine(TEXT("You ran outta Lives"));
		GameOver();
		return;
	}
}

FBullCowCount UBullCowCartridge::BullsNCows(FString Guess) const  // Return type is the STRUCT name because that is a custom data type
{
	FBullCowCount Count;										// Instance of the Struct
	for (int32 Index = 0; Index <= Guess.Len(); Index++)
	{
		if (Guess[Index] == HiddenWord[Index])
		{
			Count.Bulls++;
			continue;
		}

		for ( int32 Index2 = 0; Index2 <= Guess.Len(); Index2++)
		{
			if (Guess[Index] == HiddenWord[Index2])
			{
				Count.Cows++;
				break;
			}
				

		}

	}

	return Count;  // Return the instance instead of variables inside the Count
	
}

bool UBullCowCartridge::IsIsogram(const FString& WordL) const   //This function doesn't change any member vars
{
	bool b1 = true;
	for (int32 i=0; i<WordL.Len(); i++)
	{
		
		for (int32 j = i + 1; j<WordL.Len(); j++)         //Using Lives for HiddenWord length value
		{
			if (WordL[i] == WordL[j])
			{
				b1 = false;
				break;
			}
			
		}
	}
	
	return b1;
}
