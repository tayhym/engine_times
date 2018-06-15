//
//  FBullCowGame.hpp
//  BullCowGame
//
//  Created by Matthew Tay Han Yang on 6/12/18.
//  Copyright © 2018 Matthew Tay Han Yang. All rights reserved.
//

#ifndef FBullCowGame_hpp
#define FBullCowGame_hpp

#include <stdio.h>
#include <string>

// bulls and cows initialized to 0
struct BullCowCountStruct{
    int bulls = 0;
    int cows = 0;
};

using int32 = int;
using FString = std::string;

enum class EguessValidity {
    ok,
    too_long,
    too_short,
    spacing_between_letters,
    empty_guess,
    not_isogram
};

class FBullCowGame {
    public:
        FBullCowGame();
        void Reset(); // TODO make a more rich return value
        int32 getMaxTries() const;
        int32 getCurrentTryNumber() const;
        BullCowCountStruct submitGuess(FString guess);
        int32 getHiddenWordLength() const;
        EguessValidity getGuessValidity(FString guess);
        void printGameSummary();
    
    private:
    
        static constexpr int32 MAXTRIES = 8;
        FString hiddenWord;
        int32 currentTry;
        int32 maxTries;
        bool isIsogram(FString guess) const;
        bool isLowerCase(FString guess) const; 
    };


#endif /* FBullCowGame_hpp */
