#include <stdio.h>
#include <string.h>

void loadWord(char secretWord[], char guesses[], int guess_count);
void playHangman(char secretWord[], int *playerScore);
void showHangman(int triesLeft);

int check(char c, char guesses[], int guess_count)
{
  for (int i =0; i<guess_count; i++){
      if (guesses[i]==c)
        return 1;
    }
  return 0;
}

void loadWord(char secretWord[], char guesses[], int guess_count)
{
  int size = strlen(secretWord);

  for (int i=0; i<size; i++){
    if (check(secretWord[i],guesses,guess_count)
      printf("%c ",secretWord[i]);    //shows correctly guessed letters
    else
      printf("_ ");                   //blank spaces for unguessed letters
  }
  printf("\n");
}

