//
//  FBullCowGame.cpp
//  BullCowGame
//
//  Created by Matthew Tay Han Yang on 6/12/18.
//  Copyright © 2018 Matthew Tay Han Yang. All rights reserved.
//

#include "FBullCowGame.hpp"
#include "math.h"

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
    maxTries = MAXTRIES;
    const FString HIDDEN_WORD = "dude";
    hiddenWord = HIDDEN_WORD;
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
    } else {
        return EguessValidity::ok;
    }
}


