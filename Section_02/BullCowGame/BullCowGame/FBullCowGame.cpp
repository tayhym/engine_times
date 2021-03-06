//
//  FBullCowGame.cpp
//  BullCowGame
//
//  Created by Matthew Tay Han Yang on 6/12/18.
//  Copyright © 2018 Matthew Tay Han Yang. All rights reserved.
//

#pragma once 
#include "FBullCowGame.hpp"
#include "math.h"
#include <stdio.h>
#include <iostream>
#include <map>
#define Tmap std::map

using int32 = int;
using uint32 = unsigned int;

int32 FBullCowGame::getCurrentTryNumber() const { 
    return currentTry;
}


int32 FBullCowGame::getMaxTries() const { 
    return maxTries;
}

int32 FBullCowGame::getHiddenWordLength() const {
    return hiddenWord.length();
}

void FBullCowGame::Reset() {
    currentTry = 1;
    const FString HIDDEN_WORD = "lance";
    hiddenWord = HIDDEN_WORD;
    maxTries = wordLengthToMaxTries(hiddenWord.length());
    return;
}

FBullCowGame::FBullCowGame() {
    Reset();
    return;
}

BullCowCountStruct FBullCowGame::submitGuess(FString guess) {
    //  increment try number
    
    currentTry++;
    
    // init BullCowCountStruct
    BullCowCountStruct bull_cow_count;
    
    // loop through letters
    int32 num_letters_hidden = (int32) hiddenWord.length();
    int32 num_letters_guess = guess.length();
    uint32 num_letters_loop = fmin(num_letters_guess, num_letters_hidden);
    for (int32 i = 0; i<num_letters_hidden; i++) {
        if (hiddenWord[i] == guess[i]) {
            bull_cow_count.bulls++;
        } else {
            bull_cow_count.cows++;
        }
    }
    uint32 remaining_cows = fmax(num_letters_guess, num_letters_hidden) - num_letters_loop;
    bull_cow_count.cows += remaining_cows;
    
    return bull_cow_count;
}

EguessValidity FBullCowGame::getGuessValidity(FString guess) {
    if (guess.length() == 0) {
        return EguessValidity::empty_guess;
    } else if (guess.length() < hiddenWord.length()) {
        return EguessValidity::too_short;
    } else if (guess.length() > hiddenWord.length()) {
        return EguessValidity::too_long;
    } else if (std::count(guess.begin(), guess.end(), ' ') >=1) {
        return EguessValidity::spacing_between_letters;
    } else if (!isIsogram(guess)) {
        return EguessValidity::not_isogram;
    } else {
        return EguessValidity::ok;
    }
}

void FBullCowGame::printGameSummary() {
    std::cout << "Summary: " << std::endl;
    std::cout << "You took " << currentTry - 1 << " guess(es). " << std::endl;
    
}

bool FBullCowGame::isIsogram(FString guess) const { 
    Tmap<char, bool> letters_seen;
    for (int32 i=0; i<guess.length(); i++) {
        char guess_letter = std::tolower(guess[i]);
        if (letters_seen.find(guess_letter) == letters_seen.end())
            letters_seen[guess_letter] = true;
        else {
            return false;
        }
    }
    return true;
    
}

bool FBullCowGame::isLowerCase(FString guess) const { 
    for (auto letter : guess) {
        if (~std::islower(letter)) {
            return false;
        }
    }
    return true;
}

int32 FBullCowGame::wordLengthToMaxTries(int32 wordLength) const { 
    Tmap <int32, int32> wordLenToTries = { {1,2}, {2,4}, {3,5}, {4,8}, {5,9}, {6,15}};
    return wordLenToTries[wordLength];
}






