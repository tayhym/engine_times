//
//  main.cpp
//  BullCowGame
//
//  Created by Matthew Tay Han Yang on 5/31/18.
//  Copyright © 2018 Matthew Tay Han Yang. All rights reserved.
//

#include <iostream>
#include <string>
#include "FBullCowGame.hpp"

using FText = std::string;
using int32 = int;

void printIntro();
FText getValidGuess();
static void playGame();
bool askToPlayAgain();

//arghh.. using the same game across the plays... not sure if this is the best idea

FBullCowGame BCGame = FBullCowGame();



int main(int argc, const char * argv[]) {

    printIntro();
    bool continue_game = true;
    do {
        playGame();
        continue_game = askToPlayAgain();
        
    } while (continue_game);
    
    return 0;
}


void printIntro() {
    // print introduction
    std::cout << "Hello! Welcome to Bulls and Cows game!" << std::endl;
    std::cout << "The word has " <<BCGame.getHiddenWordLength() << " alphabets." << std::endl;
    std::cout << "Can you guess what the word is? " << "(" << BCGame.getMaxTries() << " max tries)" << std::endl;
    return;
}

FText getValidGuess() {
    // get guess from user
    FText guess = "";
    
    EguessValidity status = EguessValidity::ok;

    do {
        std::getline(std::cin, guess);
        status = BCGame.getGuessValidity(guess);
        switch (status) {
            case EguessValidity::empty_guess:
                std::cout << "Your guess must not be empty. Please try again. " << std::endl;
                break;
            case EguessValidity::too_long:
                std::cout << "The guess is too long. Please try again. " << std::endl;
                break;
            case EguessValidity::too_short:
                std::cout << "The guess is too short. Please try again. " << std::endl;
                break;
            case EguessValidity::spacing_between_letters:
                std::cout << "The guess is not a single word. Please try again. " << std::endl;
                break;
            case EguessValidity::ok:
                break;
            }
        } while (status != EguessValidity::ok);
    
    return guess;
}

static void playGame() {

    std::cout << "Please enter your guess" << std::endl;
    
    FText guess = "";
    
    while (BCGame.getCurrentTryNumber() < BCGame.getMaxTries()) {
        guess = getValidGuess();
        
        std::cout << "Current try number: " << BCGame.getCurrentTryNumber() << std::endl;
        std::cout << "Maximum # of Tries: " << BCGame.getMaxTries() << std::endl;
        BullCowCountStruct bull_cow_count = BCGame.submitGuess(guess);
        std::cout << "Bulls: " << bull_cow_count.bulls << " Cows: " << bull_cow_count.cows << std::endl;
        
        if (bull_cow_count.bulls == BCGame.getHiddenWordLength()) {
            std::cout << "Congratulations, you got the right word!" << std::endl;
            return;
        } else {
             std::cout << "Aww. Incorrect word. You may try again " << std::endl;
        }
       
    }
    std::cout << "Game over! Max tries reached. " << std::endl;
}


bool askToPlayAgain() {
    FText response = "";
    std::cout << "Do you want to play again?" << std::endl;
    std::getline(std::cin, response);
    return response[0] == 'y' || response[0] == 'Y';
}
