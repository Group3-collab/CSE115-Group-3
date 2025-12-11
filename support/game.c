#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include "game.h"

#define MAX_TRIES 7

// Chooses a random word from the list
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

// Checks if a letter has already been guessed
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
void initialReveal(const char *secretWord, char guesses[], int *guessCount) {
    int wordSize = strlen(secretWord);
    
    //Determines the number of letters to reveal
    int revealCount = wordSize/5;
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

// Updates the progress array (e.g. "_a__ma_")
void updateProgress(const char *secretWord, char guesses[], int *guessCount, char *gameProgress)
{
    int wordSize = strlen(secretWord);

    for (int i=0; i < guessCount; i++)
    {
        if (checkifGuessed(secretWord[i], guesses, guessCount))
            gameProgress[i]=secretWord[i];
        else
            gameProgress[i]='_';
    }
    gameProgress[wordSize]='\0';
}

// Displays the progress string
void displayProgress(const char *gameProgress)
{
    int wordSize = strlen(gameProgress);

    printf("\nWord:\t");
    for (int i=0; i < wordSize; i++)
        printf("%c ",gameProgress[i]);
    printf("\n");
}

// Checks if the word is fully guessed
int checkWin(const char *gameProgress)
{
    int wordSize = strlen(gameProgress);

    for (int i=0; i < wordSize; i++)
    {
        if (gameProgress[i]=='_')
            return 0;
    }
    return 1;
}

// Gets a single letter guess from user, ignoring invalid characters
char getPlayerGuess()
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

// Processes the guess: update guessed letters & return correct/incorrect
int processGuess(char playerGuess, const char *secretWord, char guesses[], int *guessCount)
{
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

// Draws the hangman based on remaining lives
void showHangman(int triesLeft)
{
    static const char *HANGMAN_STAGES[] = {
        "  _______\n"
        " |       |\n"
        " |       O\n"
        " |      /|\\\n"
        " |      / \\\n"
        " |\n"
        "_|_\n",

        "  _______\n"
        " |       |\n"
        " |       O\n"
        " |      /|\\\n"
        " |      /\n"
        " |\n"
        "_|_\n",

        "  _______\n"
        " |       |\n"
        " |       O\n"
        " |      /|\\\n"
        " |\n"
        " |\n"
        "_|_\n",

        "  _______\n"
        " |       |\n"
        " |       O\n"
        " |      /|\n"
        " |\n"
        " |\n"
        "_|_\n",

        "  _______\n"
        " |       |\n"
        " |       O\n"
        " |       |\n"
        " |\n"
        " |\n"
        "_|_\n",

        "  _______\n"
        " |       |\n"
        " |       O\n"
        " |\n"
        " |\n"
        " |\n"
        "_|_\n",

        "  _______\n"
        " |       |\n"
        " |\n"
        " |\n"
        " |\n"
        " |\n"
        "_|_\n",

        "  _______\n"
        " |\n"
        " |\n"
        " |\n"
        " |\n"
        " |\n"
        "_|_\n"
    };
    
    int stage = MAX_TRIES - tries_left;

    if (stage < 0) stage = 0;
    if (stage > MAX_TRIES) stage = MAX_TRIES;

    printf("%s\n", HANGMAN_STAGES[stage]);
}


// Main gameplay engine
void playHangman(const char *secretWord, char *playerName, int *playerScore)
{
    char lettersGuessed[50];
    int guessCount = 0;
    int triesLeft = MAX_TRIES;
    char gameProgress[100];

    //Game initialization
    initialReveal(secretWord, lettersGuessed, &guessCount);
    updateProgress(secretWord, lettersGuessed, &guessCount, gameProgress);

    printf("Welcome, %s! Let's see if you can guess this word. Good luck!\n\n", playerName);

    while (triesLeft > 0) {
        showHangman(triesLeft);
        displayProgress(gameProgress);
        printf("Guesses left: %d\n", triesLeft);

        //Gets player guess
        char guess = getPlayerGuess();

        if (checkifGuessed(guess, lettersGuessed, guessCount)) {
            printf("You've already guessed '%c'. Try another letter.\n", guess);
            continue;
        }

        //Records guess to array of guesses
        lettersGuessed[guessCount++] = guess;

        //Processes guess
        int correct = processGuess(guess, secretWord, lettersGuessed, &guessCount);
        if (!correct) {
            triesLeft--;
            printf("Incorrect guess...\n");
        }
        else
            printf("Good guess!\n");

        //Updates progress
        updateProgress(secretWord, lettersGuessed, &guessCount, gameProgress);

        //Checks if game was won
        if (checkWin(gameProgress)) {
            printf("\nYOU WIN, %s!\n", playerName);
            printf("The word was: %s\n", secretWord);

            //Score update
            *playerScore += 10;

            return;
        }
    }

    //Game lost
    showHangman(0);
    printf("\nYou lost, %s. The word was: %s\n", playerName, secretWord);
}









