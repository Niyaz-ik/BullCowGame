/*FText in main.cpp
FString in other, class*/

/*Это исполняемый консолью файл, который использует класс BullCow.
Он действует как вид в шаблоне MVC(модель, вид, контроллер) и отвечает за
взаимодействие с пользователем. Для того, чтобы увидеть игровую логику
смотрите класс "FBullCowGame*/

#pragma once

#include <iostream>
#include <string>
#include "FBullCowGame.h"

using FText = std::string;
using int32 = int;

void IntroGame();
FText GetValidGuess();
void PlayGame();
bool AskPlayerRepeat();
void PrintGameSummary();

FBullCowGame BCGame; // instantiate a new game

int main() {
	IntroGame();

	do {
		PlayGame();
		PrintGameSummary();
	}while (AskPlayerRepeat());
	return 0;
};

void IntroGame() {			//display the "welcome" screen
	int32 HiddenWordLength = BCGame.GetHiddenWordLength();
	std::cout << "Welcome to Bulls and Cows, a fan word game!\n";
	std::cout << "                }     {              _____ \n";
	std::cout << "                (O   O)             (O   O)   \n";
	std::cout << "    /------------\\   /               \\   /-----------\\ \n";
	std::cout << "   / |   BULL   |  O                   O|    COW    | \\ \n";
	std::cout << "  *  |--,-------|                       |-----------|  * \n";
	std::cout << "     ^          ^                       ^           ^   \n";
	std::cout << "Can you guess the " << HiddenWordLength << " letter isogram I'm thinking of?\n";
	return;
}

FText GetValidGuess() {		//get guess from player
	FText Guess = "";
	EGuessStatus Status = EGuessStatus::Invalid_Status;
	do {
		int32 CurrentTry = BCGame.GetCurrentTry();
		std::cout << "Try " << CurrentTry << " of " << BCGame.GetMaxTries() << "        Enter your guess: ";
		std::getline(std::cin, Guess);

		EGuessStatus Status = BCGame.CheckGuessValidity(Guess);
		switch (Status) {
		case EGuessStatus::Wrong_Length:
			std::cout << "Please enter a " << BCGame.GetHiddenWordLength() << " letter word.\n\n";
			break;
		case EGuessStatus::Not_Isogram:
			std::cout << "Please enter a word without repeating letters.\n\n";
			break;
		case EGuessStatus::Not_LowerCase:
			std::cout << "Please enter all lowercase letter.\n\n";
			break;
		default:
			return Guess;
		}
	} while (Status != EGuessStatus::OK);
}

void PlayGame() {
	int32 MaxTries = BCGame.GetMaxTries();
		
	while (!BCGame.IsGameWon() && BCGame.GetCurrentTry() <= BCGame.GetMaxTries()) {
			FText Guess = GetValidGuess();

			FBullCowCount BullCowCount = BCGame.SubmitValidGuess(Guess);

			std::cout << "Bull: " << BullCowCount.Bull << ". Cow:" << BullCowCount.Cow << std::endl;

			std::cout << "\nYour guess was: " << Guess << std::endl;
			std::cout << std::endl;
		}
	return;
}

bool AskPlayerRepeat() {
	BCGame.Reset();
	std::cout << "Do you want to play again (y/n)?";
	FText answer = "";
	std::getline(std::cin, answer);
	if ((answer[0] == 'y') || (answer[0] == 'Y')) {
		return true;
	};
	return false;
}

void PrintGameSummary()
{
	if (BCGame.IsGameWon()) {
		std::cout << "YOU ARE A WINNER!!!\n\n";
		return;
	}
	else {
		std::cout << "YOU ARE A LOOSER!!!\n\n";
		return;
	}
}
