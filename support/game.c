#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include "game.h"

// Choose a random word from the list
int chooseWord(const char *fileName, char *secretWord, int maxSize)
{
    FILE *file = fopen(filename,"r");
    if (!file) {
        printf("Error: Could not open file\n");
        return 0;    //failure
    }

    char words[200][50];    //Row = word count, column = word length
    int count = 0;

    //Reads words from file
    while (fgets(words[count], sizeof(words[count]), file) != NULL) {
        words[count][strcspn(words[count],"\n")] = '\0';    //Removes newline
        count++;

        if (count >= 200)
            break;
    }

    fclose(file);

    if (count == 0) {
        printf("Error: No words found in file\n");
        return 0;       //failure
    }

    //Random index
    int index = rand() % count;

    //Copies into output
    strncpy(secretWord, words[index], maxSize-1);
    secretWord[maxSize-1] = '\0';
    
    return 1;  // success
}

// Check if a letter has already been guessed
int checkifGuessed(char c, char guesses[], int guessCount)
{
    for (int i=0; i < guessCount; i++)
    {
        if (guesses[i]==c)
            return 1;   //found
    }
    return 0;           // not found
}

//Reveals part of the secret word initially
void initialReveal(const char *secretWord, char guesses[], int *guessCount, int revealCount) {
    int wordSize = strlen(secretWord);

    //Avoids revealing more words than present
    if (revealCount > wordSize)
        revealCount = wordSize/5;
    while (*guessCount < revealCount) {
        int index = rand() % wordSize;
        char reveal = secretWord[index];
        
        //Checks if already guessed
        int guessed = 0;
        for (int i=0; i < *guessCount; i++) {
            if (guesses[i] == reveal) {
                guessed = 1;
                break;
            }
        }
        
        //Adds letter if new
        if (!guessed) {
            guesses[*guessCount] = reveal;
            (*guessCount)++;
        }
    }
}

// Update the progress array (e.g. "_a__ma_")
void updateProgress(const char *secretWord, char guesses[], int *guessCount, char gameProgress[])
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
    char buffer[50];
    char playerGuess;

    while(1){
        printf("Enter a letter: ");

        if (fgets(buffer, sizeof(buffer),stdin)==NULL)
            continue;

        int i=0;
        while (buffer[i]=='\n')
            i++;

        playerGuess = buffer[i];

        if(!isalpha(playerGuess)){
            printf("Please enter a valid character (A-Z)\n");
            continue;
        }

        playerGuess = tolower(playerGuess);
        return playerGuess;
    }
}

// Process the guess: update guessed letters & return correct/incorrect
int processGuess(char playerGuess, const char *secretWord, char guesses[], int *guessCount)
{
    //Checks if player input has already been guessed
    if (checkifGuessed(playerGuess, guesses, *guessCount))
        return -1;        //Already guessed

    //Adds player input to guesses[]
    guesses[*guessCount] = guess;
    (*guessCount)++;
    
    //Checks if player input appears in secret word
    for (int i=0; word[i] != '\0'; i++) {
        if (secretWord[i] == playerGuess)
            return 1;    //Correct guess
    }
    
    return 0;            //Incorrect guess
}

// Optional: draw the hangman based on remaining lives
void showHangman(int triesLeft)
{
    // TODO: ASCII art for lives 6→0
}

// Main gameplay engine
void playHangman(const char *secretWord, char *playerName, int *playerScore)
{
    // TODO:
    // - set lives (e.g. triesLeft = 6)
    // - create guessed_letters array
    // - create progress array with correct length
    // - game loop:
    //       updateProgress()
    //       displayProgress()
    //       playerGuess()
    //       processGuess()
    //       update tiresLeft if incorrect
    //       checkWin()
    // - print win/lose result
    // Update playerScore
}







