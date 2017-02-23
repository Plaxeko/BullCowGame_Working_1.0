/*The Game logic (no view code or direct user interaction
This game is a simple guess the word game based on Mastermind */

#pragma once
#include <string>

//unreal friendly syntax
using FString = std::string;
using int32 = int;


struct FBullCowCount 
{
	int32 Bulls = 0;
	int32 Cows = 0;
};

enum class EDifficultyStatus 
{
	Invalid_Status,
	OK, 
	Not_Number,
	Not_Range

};

enum class EGuessStatus 
{
	Invalid_Status,
	OK,
	Not_Isogram,
	Wrong_Length,
	Not_Lower_Case

};

//interface
class FBullCowGame 
{

public: 

	FBullCowGame(); //constructor 

	int32 GetMaxTries() const;
	int32 GetCurrentTry() const;
	int32 GetHiddenWordLength() const;
	
	bool IsGameWon() const;

	FString GetHiddenWord(FString Difficulty) const;

	EDifficultyStatus CheckDIfficultyValidity(FString) const;
	EGuessStatus CheckGuessValidity(FString) const;

	void Reset(FString Difficulty);  
	
	FBullCowCount SubmitValidGuess(FString);

private:
	//See constructor for initialization
	int32 MyCurrentTry;

	bool bGameIsWon;
	bool IsIsogram(FString) const;
	bool IsLowercase(FString) const;
	bool IsNumb(FString Difficulty) const;
	bool IsRange(int Difficulty) const;
	
};