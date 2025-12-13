#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include "game.h"

#define MAX_TRIES 6

// Chooses a random word from the list
const char* chooseWord(const char *wordList[], int wordCount)
{
    if (wordCount <= 0)
        return NULL;

    int randomIndex = rand() % wordCount;
    return wordList[randomIndex];
}

// Checks if a letter has already been guessed
int checkifGuessed(char c, char guesses[], int guessCount)
{
    for (int i = 0; i < guessCount; i++)
    {
        if (guesses[i] == c)
            return 1;   //found
    }
    return 0;           // not found
}

// Updates the progress array (e.g. "_a__ma_")
void updateProgress(const char *secretWord, char guesses[], int guessCount, char gameProgress[])
{
    int wordSize = strlen(secretWord);

    for (int i = 0; i < wordSize; i++)
    {
        if (checkifGuessed(secretWord[i], guesses, guessCount))
            gameProgress[i] = secretWord[i];
        else
            gameProgress[i] = '_';
    }
    gameProgress[wordSize] = '\0';
}

// Displays the progress string
void displayProgress(const char *gameProgress)
{
    int wordSize = strlen(gameProgress);

    printf("\nWord:\t");
    for (int i = 0; i < wordSize; i++)
        printf("%c ", gameProgress[i]);
    printf("\n");
}

// Checks if the word is fully guessed
int checkWin(const char *gameProgress)
{
    int wordSize = strlen(gameProgress);

    for (int i = 0; i < wordSize; i++)
    {
        if (gameProgress[i] == '_')
            return 0;
    }
    return 1;
}

// Gets a single letter guess from user, ignoring invalid characters
char playerGuess()
{
    char buffer[50];
    char guess;

    while(1)
    {
        printf("\nEnter a letter: ");

        if (fgets(buffer, sizeof(buffer), stdin) == NULL)
            continue;

        int i = 0;
        while (buffer[i] == ' ' || buffer[i] == '\t')
            i++;

        guess = buffer[i];

        if (!isalpha(guess))
        {
            printf("Please enter a valid character (A-Z)\n");
            continue;
        }

        guess = tolower(guess);
        return guess;
    }
}

// Processes the guess: update guessed letters & return correct/incorrect
int processGuess(char playerGuess, const char *secretWord, char guesses[], int *guessCount)
{
    //Adds player input to guesses[]
    guesses[*guessCount] = playerGuess;
    (*guessCount)++;

    //Checks if player input appears in secret word
    for (int i = 0; secretWord[i] != '\0'; i++)
    {
        if (secretWord[i] == playerGuess)
            return 1;    //Correct guess
    }

    return 0;            //Incorrect guess
}

// Draws the hangman based on remaining lives
void showHangman(int triesLeft)
{
    static const char *HANGMAN_STAGES[] = {
        // Stage 0: Empty gallows (6 tries left)
        "  _______\n"
        " |       |\n"
        " |\n"
        " |\n"
        " |\n"
        " |\n"
        "_|_\n",

        // Stage 1: Head (5 tries left)
        "  _______\n"
        " |       |\n"
        " |       O\n"
        " |\n"
        " |\n"
        " |\n"
        "_|_\n",

        // Stage 2: Body (4 tries left)
        "  _______\n"
        " |       |\n"
        " |       O\n"
        " |       |\n"
        " |\n"
        " |\n"
        "_|_\n",

        // Stage 3: Left arm (3 tries left)
        "  _______\n"
        " |       |\n"
        " |       O\n"
        " |      /|\n"
        " |\n"
        " |\n"
        "_|_\n",

        // Stage 4: Both arms (2 tries left)
        "  _______\n"
        " |       |\n"
        " |       O\n"
        " |      /|\\\n"
        " |\n"
        " |\n"
        "_|_\n",

        // Stage 5: Left leg (1 try left)
        "  _______\n"
        " |       |\n"
        " |       O\n"
        " |      /|\\\n"
        " |      /\n"
        " |\n"
        "_|_\n",

        // Stage 6: Both legs - GAME OVER (0 tries left)
        "  _______\n"
        " |       |\n"
        " |       O\n"
        " |      /|\\\n"
        " |      / \\\n"
        " |\n"
        "_|_\n"
    };

    int stage = MAX_TRIES - triesLeft;

    if (stage < 0) stage = 0;
    if (stage > 6) stage = 6;

    printf("%s\n", HANGMAN_STAGES[stage]);
}

// Main gameplay engine
void playHangman(const char *secretWord, int *playerScore)
{
    char lettersGuessed[50];
    int guessCount = 0;
    int triesLeft = MAX_TRIES;
    char gameProgress[100];

    //Game initialization
    updateProgress(secretWord, lettersGuessed, guessCount, gameProgress);

    printf("The word has %d letters. Good luck!\n", (int)strlen(secretWord));

    while (triesLeft > 0)
    {
        showHangman(triesLeft);
        displayProgress(gameProgress);
        printf("Guesses left: %d\n", triesLeft);

        //Gets player guess
        char guess = playerGuess();

        if (checkifGuessed(guess, lettersGuessed, guessCount))
        {
            printf("You've already guessed '%c'. Try another letter.\n", guess);
            continue;
        }

        //Processes guess
        int correct = processGuess(guess, secretWord, lettersGuessed, &guessCount);
        if (!correct)
        {
            triesLeft--;
            printf("Incorrect guess...\n");
        }
        else
            printf("Good guess!\n");

        //Updates progress
        updateProgress(secretWord, lettersGuessed, guessCount, gameProgress);

        //Checks if game was won
        if (checkWin(gameProgress))
        {
            printf("\n+----------------------------------------+\n");
            printf("|       CONGRATULATIONS! YOU WIN!        |\n");
            printf("+----------------------------------------+\n");
            displayProgress(gameProgress);

            //Score update
            int scoreGained = triesLeft * 10;
            *playerScore += scoreGained;
            printf("\nYou earned %d points!\n", scoreGained);

            return;
        }
    }

    //Game lost
    showHangman(0);
    printf("\n+----------------------------------------+\n");
    printf("|          GAME OVER! YOU LOST!          |\n");
    printf("+----------------------------------------+\n");
    printf("\nThe word was: %s\n", secretWord);
}

// Frees memory allocated for word list
void freeWordList(const char *wordList[], int wordCount)
{
    for (int i = 0; i < wordCount; i++)
    {
        if (wordList[i] != NULL)
        {
            free((void *)wordList[i]);
        }
    }
}




