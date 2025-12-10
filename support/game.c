#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include "game.h"

// Choose a random word from the list
const char* chooseWord(const char *word_list[], int wordCount)
{
    // TODO: use rand() % word_count to pick a random index
    return NULL;  // placeholder
}

// Check if a letter has already been guessed
int checkifGuessed(char c, char guesses[], int guessCount)
{
    // TODO: loop through guesses[] and return 1 if found
    for (int i=0; i<guessCount; i++)
    {
        if (guesses[i]==c)
            return 1;   //found
    }
    return 0;           // not found
}

// Update the progress array (e.g. "_a__ma_")
void updateProgress(const char *secretWord, char guesses[], int guessCount, char gameProgress[])
{
    int wordSize = strlen(secretWord);

    for (int i=0; i<guessCount; i++)
    {
        if (checkifGuessed(secretWord[i], guesses, guessCount))
            gameProgress[i]=secretWord[i];
        else
            gameProgress[i]='_';
    }
    gameProgress[wordSize]='\0';
}

// Display the progress string
void displayProgress(const char *gameProgress)
{
    int size = strlen(gameProgress);

    printf("Word:\t");
    for (int i=0; i<size; i++)
        printf("%c ",gameProgress[i]);
    printf("\n");
}

// Check if the word is fully guessed
int checkWin(const char *gameProgress)
{
    int size = strlen(gameProgress);

    for (int i=0; i<size; i++)
    {
        if (gameProgress[i]=='_')
            return 0;
    }
    return 1;
}

// Get a single letter guess from user
char playerGuess()
{
    // TODO:
    // - read a line from input
    // - take first non-newline character
    // - convert to lowercase
    // - ignore non-alphabetic inputs
    return '\0';  // placeholder
}

// Process the guess: update guessed letters & return correct/incorrect
int processGuess(char playerGuess, const char *secretWord, char guesses[], int *guessCount)
{
    // TODO:
    // - check if guess already in guesses[] (optional)
    // - add guess to guesses[]
    // - increment *guess_count
    // - return 1 if guess appears in word, else 0
    return 0;
}

// Optional: draw the hangman based on remaining lives
void showHangman(int triesLeft)
{
    // TODO: ASCII art for lives 6→0
}

// Main gameplay engine
void playHangman(const char *secretWord, int* playerScore)
{
    // TODO:
    // - set lives (e.g. lives = 6)
    // - create guessed_letters array
    // - create progress array with correct length
    // - game loop:
    //       update_progress()
    //       display_progress()
    //       get_player_guess()
    //       process_guess()
    //       update lives if incorrect
    //       check is_word_guessed()
    // - print win/lose result
}
