#ifndef GAME_H_INCLUDED
#define GAME_H_INCLUDED

//Chooses random word from list, returns success or failure
int chooseWord(const char *fileName, char *secretWord, int maxSize);

//Checks if a letter has already been guessed
int checkifGuessed(char c, char guesses[], int guessCount);

//Reveals part of the secret word
void initialReveal(const char *secretWord, char guesses[], int *guessCount);

//Updates the string with how many letters have been guessed
void updateProgress(const char *secretWord, char guesses[], int *guessCount, char gameProgress[]);

//Displays the progress of the game
void displayProgress(const char *gameProgress);

//Checks if game has been won
int checkWin(const char *gameProgress);

//Gets player input
char getPlayerGuess();

//Processes player input: adds guessed char to guesses array and returns if correct/incorrect
int processGuess(char playerGuess, const char *secretWord, char guesses[], int *guessCount);

//Draws the hangman
void showHangman(int triesLeft);

//Main function to play game
void playHangman(const char *secretWord, char *playerName, int *playerScore);

#endif //GAME_H_INCLUDED
