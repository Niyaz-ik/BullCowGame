/* The game logic (no view code or direct user interaction)*/

#pragma once
#include <string>

// to make syntax Unreal friendly
using FString = std::string;
using int32 = int;

struct FBullCowCount
{
	int32 Bull = 0;
	int32 Cow = 0;
};

enum class EGuessStatus {
	Invalid_Status,
	OK,
	Not_Isogram,
	Wrong_Length,
	Not_LowerCase
};

class FBullCowGame {
public:
	FBullCowGame(); //constructor

	int32 GetMaxTries() const;
	int32 GetCurrentTry() const;
	int32 GetHiddenWordLength() const;
	//int32 GetDifficult(int32);

	bool IsGameWon() const;
	EGuessStatus CheckGuessValidity(FString) const;
	
	//FString GetHiddenWord();
	void Reset();
	FBullCowCount SubmitValidGuess(FString);


private: 
	int32 MyCurrentTry;
	FString MyHiddenWord;
	bool bGameIsWon;
	int32 MyDifficult;

	bool IsIsogram(FString) const;
	bool IsLowercase(FString) const;
};