
#pragma once

#include "FBullCowGame.h"
#include <iostream>
#include <string>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <map>

//unreal friendly syntax
#define TMap std::map 
using int32 = int;

FString MyHiddenWord = "";
FString Difficulty = "";

FBullCowGame::FBullCowGame() { Reset(Difficulty); } //default constructor

int32 FBullCowGame::GetCurrentTry() const { return MyCurrentTry; }

int32 FBullCowGame::GetHiddenWordLength() const { return MyHiddenWord.length(); }

bool FBullCowGame::IsGameWon() const { return bGameIsWon; }

FString FBullCowGame::GetHiddenWord(FString Difficulty) const
{
	TMap<FString, FString> MyHiddenWord{ {"1", "pan"}, {"2", "song"}, {"3", "breath"}, {"4", "planet"}, {"5", "kingdom"} };
	return MyHiddenWord[Difficulty];
}



int32 FBullCowGame::GetMaxTries() const 
	{ 
		TMap<int32, int32> WordLengthToMaxTries{ { 3, 5 }, { 4, 10 }, { 5, 15 }, {6, 20}, {7, 25} };
		return WordLengthToMaxTries[MyHiddenWord.length()] ;
	}


void FBullCowGame::Reset(FString Difficulty)
	{
		//const FString HIDDEN_WORD = "planet";//This must be an isogram
		MyHiddenWord = GetHiddenWord(Difficulty);
		MyCurrentTry = 1;
		bGameIsWon = false;
		return;
	}


EDifficultyStatus FBullCowGame::CheckDIfficultyValidity(FString Difficulty) const
{
	if (!IsNumb(Difficulty))
	{
		return EDifficultyStatus::Not_Number;
	}
	else if (!IsRange(std::stoi(Difficulty)))
	{
		return EDifficultyStatus::Not_Range;
	}
	else
	{
		return EDifficultyStatus::OK;
	}
	
	return EDifficultyStatus::OK;
}



EGuessStatus FBullCowGame::CheckGuessValidity(FString Guess) const
{
	if (!IsIsogram(Guess))	 
	{
		return EGuessStatus::Not_Isogram;
	}
	else if (!IsLowercase(Guess))	  
	{
		return EGuessStatus::Not_Lower_Case; 
	}
	else if (Guess.length() != GetHiddenWordLength()) 
	{
		return EGuessStatus::Wrong_Length;
	}
	else
	{
		return EGuessStatus::OK;
	}
	return EGuessStatus::OK; 
}


//counts bulls and cows. Also increases turn number assuming VALID guess
FBullCowCount FBullCowGame::SubmitValidGuess(FString Guess)
{
	MyCurrentTry++;
	FBullCowCount BullCowCount;

	// loop through all letters in the hidden word
	int32 WordLength = MyHiddenWord.length(); //assuming same length as guess
	for (int32 MHWChar = 0; MHWChar < WordLength; MHWChar++)
	{
		// compare letters against the guess
		for (int32 GChar = 0; GChar < WordLength; GChar++)
		{
			// if they match then
			if (Guess[GChar] == MyHiddenWord[MHWChar])
			{
				if (MHWChar == GChar)
				{ 
					BullCowCount.Bulls++; 
				}
				else
				{
					BullCowCount.Cows++; 
				}
			}
		}
	}
	if (BullCowCount.Bulls == WordLength)
	{
		bGameIsWon = true;
	}
	else
	{
		bGameIsWon = false;
	}
	return BullCowCount;
}


bool FBullCowGame::IsIsogram(FString Word) const
{

	// treat 0 and 1 letter words as isograms
	if (Word.length() <= 1)
	{
		return true;
	}
	
	TMap<char, bool> LetterSeen;

	for (auto Letter : Word) //This means "For all letters of the word"
	{
		Letter = tolower(Letter);

		if (LetterSeen[Letter])
		{
			return false;
		}
		else
		{
			LetterSeen[Letter] = true; //add the letter to the map
		}
							
	}

	return true;
}



bool FBullCowGame::IsLowercase(FString Word) const
{	
	for (auto Letter : Word)
	{
											  
		if (!islower(Letter))
		{
			return false;
		}	
	}
	return true;
}

bool FBullCowGame::IsNumb(FString Difficulty) const
{
	char *cstr = &Difficulty[0u];
	
	if (isdigit(*cstr))
	{
		return true;
	}
	else
	{
		return false;
	}
	
	return false;
}

bool FBullCowGame::IsRange(int Difficulty) const
{
 	if (((Difficulty) >= 1) && ((Difficulty) <= 5))
	{
		return true; 
	}
	else
	{
		return false;
	}
	return false;
}

