/*
This is the console executable that makes use of the BullCow class
This acts as the view in a MVC pattern, and is responsble for all user interaction.
For game logic, see the FBullCowGame class. 
*/
#pragma once
#include <iostream>
#include <string>
#include "FBullCowGame.h"

//to make syntax unreal friendly
using FText = std::string;
using int32 = int; 

//function prototypes as outside a class
void PrintIntro();
void PlayGame();
FText GetValidDifficulty();
FText GetValidGuess();
bool AskToPlayAgain();
void PrintGameSummary();


FBullCowGame BCGame; // instantiate new game used across plays


int32 main() 
{

	bool bPlayAgain = false; 
	do 
	{

		PrintIntro();
		GetValidDifficulty();
		PlayGame(); 
		bPlayAgain = AskToPlayAgain();

	} while (bPlayAgain);
	
	return 0;
}


void PrintIntro()
{

	std::cout << " \n Welcome to Bulls and Cows, a fun word game. \n";
	std::cout << R"(
                ((___))    |         \___/
    ____________( 0 o )    |        ( o 0 )____________
   /     ::::    \   /     | (:)     \   /    ::::     \
  / |    BULL    (` ')     |  |      (` ')    COW     | \
_/_/| |  :::: | |_(U)|____\|/\|/____ |   _| | ::::  | |\_\_ _____
    | || |~~~~| |  | |               | |  | |~~~~| || |
   /..\..\    /..\/..\               /..\/..\    /../..\
)" << "\n"; 
	

	
	std::cout << std::endl;		
	return;
}


//plays a single game through complete
void PlayGame()
{
	
	int32 MaxTries = BCGame.GetMaxTries();

	
	 																								
	while (!BCGame.IsGameWon() && BCGame.GetCurrentTry() < MaxTries)
	{
		FText Guess = GetValidGuess(); 

		FBullCowCount BullCowCount = BCGame.SubmitValidGuess(Guess);
		

		std::cout << "Bulls = " << BullCowCount.Bulls;
		std::cout << ". Cows = " << BullCowCount.Cows << "\n\n";
	}
	PrintGameSummary();
	return;
}

FText GetValidDifficulty()
{
	FText Difficulty = "";
	EDifficultyStatus DStatus = EDifficultyStatus::Invalid_Status;

	do
	{
	
		std::cout << "Select a difficulty between 1 (easy) - 5 (impossible): ";
		std::getline(std::cin, Difficulty);

		//std::cin >> Difficulty;
		BCGame.Reset(Difficulty);
		DStatus = BCGame.CheckDIfficultyValidity(Difficulty);
		std::cout << std::endl;
		switch (DStatus)
		{
		case EDifficultyStatus::Not_Number:
			std::cout << "Please only enter numbers \n\n";
			break;
		case EDifficultyStatus::Not_Range:
			std::cout << "Please enter a number within range. \n\n";
			break;
		default:
			break;
		}
	} while (DStatus != EDifficultyStatus::OK);

	std::cout << std::endl;
	std::cout << "Can you guess the " << BCGame.GetHiddenWordLength() << " letter isogram I'm thinking of? \n\n";

	return Difficulty;
	
}



FText GetValidGuess() 
{
	FText Guess = "";
	EGuessStatus Status = EGuessStatus::Invalid_Status;
	do
	{
		
		int32 CurrentTry = BCGame.GetCurrentTry();
		std::cout << "Try " << BCGame.GetCurrentTry() << " of " << BCGame.GetMaxTries() << ". Enter your Guess: ";
		std::getline(std::cin, Guess);

		Status = BCGame.CheckGuessValidity(Guess);

		switch (Status)
		{
		case EGuessStatus::Wrong_Length:
			std::cout << "Please enter a " << BCGame.GetHiddenWordLength() << " letter word. \n\n";
			break;
		case EGuessStatus::Not_Lower_Case:
			std::cout << "Please enter lower-case letters only. \n\n";
			break;
		case EGuessStatus::Not_Isogram:
			std::cout << "Please enter a word without repeating letters. \n\n";
			break;
		default: 
			break;
		}
	} while (Status != EGuessStatus::OK); 
	
	return Guess;
}

bool AskToPlayAgain()
{
	
	std::cout << "Do you want to play again? \n\n Type Yes or No ";
	FText Response = "";
	std::getline(std::cin, Response);
	return  (Response[0] == 'Y') || (Response[0] == 'y');

}

void PrintGameSummary()
{
	if (BCGame.IsGameWon())
	{
		std::cout << "YOU WON! \n\n";
	}
	else
	{
		std::cout << "SORRY! TRY AGAIN! \n\n";
	}
	return;
}
	