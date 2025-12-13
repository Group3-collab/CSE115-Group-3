#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "support/game.h"
#include "support/player.h"
#include <time.h> // I'm adding this for pseudo random

int main()
{
    srand(time(NULL));

    printf("+----------------------------------------+\n");
    printf("|     WELCOME TO THE HANGMAN GAME!       |\n");
    printf("+----------------------------------------+\n\n");

    char playerName[50];
    int playerScore = 0;
    char choice;

    printf("Enter your name: ");
    getPlayerName(playerName, 50);

    printf("\nHello, %s! Let's play Hangman!\n\n", playerName);

    const char *wordList[50];
    int wordCount = 0;

    if (loadWordsFromFile("data/words.txt", wordList, &wordCount) == 0) {
        printf("Loaded %d words from dictionary.\n\n", wordCount);
    } else {
        printf("Could not load words file. Using default word list.\n\n");
        wordList[0] = "programming";
        wordList[1] = "computer";
        wordList[2] = "keyboard";
        wordList[3] = "software";
        wordList[4] = "hardware";
        wordList[5] = "function";
        wordList[6] = "variable";
        wordList[7] = "algorithm";
        wordList[8] = "database";
        wordList[9] = "network";
        wordCount = 10;
    }

    do {
        printf("\n-------------------------------------\n");
        printf("         NEW ROUND START!!!\n");
        printf("----------------------------------------\n\n");

        const char *secretWord = chooseWord(wordList, wordCount);

        playHangman(secretWord, &playerScore);

        printf("\n-------------------------------------\n");
        printf("Your current score: %d points\n", playerScore);
        printf("----------------------------------------\n");

        printf("\nDo you want to play again? (y/n): ");
        scanf(" %c", &choice);
        while(getchar() != '\n');

    } while (choice == 'y' || choice == 'Y');

    printf("+========================================+\n");
    printf("|             GAME OVER                  |\n");
    printf("+========================================+\n\n");

    savePlayerScore(playerName, playerScore);

    printf("Final Score for %s: %d points\n\n", playerName, playerScore);

    printf("============= HIGH SCORES =============\n");
    displayHighScores();

    printf("\nThanks for playing our game, %s!\n", playerName);

    freeWordList(wordList, wordCount);

    return 0;
}
