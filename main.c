#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "game.h"
#include "player.h"

void main()
{
char word[20] = "PROGRAMMING";
    char guessed[26] = "AEI";
    char display[20];
    int lives = 4, length;
    
    length = strlen(word);

    
        display[i] = '_';
    }
    display[length] = '\0';

    for(int pos = 0; pos < length; pos++) {
        for(int g = 0; g < strlen(guessed); g++) {
            if(word[pos] == guessed[g]) {
                display[pos] = word[pos];
                break; 
            }
        }
    }
    
    printf("\n");
    printf("   ____\n");
    printf("  |    |\n");
    printf("  O    |\n");
    
    if(lives >= 3) {
        printf("       |\n");
        printf("       |\n");
    } else if(lives >= 2) {
        printf("  |    |\n");
        printf("       |\n");
    } else if(lives >= 1) {
        printf(" /|    |\n");
        printf("       |\n");
    } else {
        printf(" /|\\   |\n");
        printf(" / \\   |\n");
    }
    
    printf("       |\n");
    printf("  ========\n");
    
    printf("\n*** HANGMAN GAME ***\n");
    printf("Hidden Word: ");
    for(int i = 0; i < length; i++) {
        printf("%c ", display[i]);
    }
    
    printf("\nLetters Used: ");
    for(int i = 0; i < strlen(guessed); i++) {
        printf("%c", guessed[i]);
        if(i < strlen(guessed) - 1) printf(", ");
    }
    
    printf("\nRemaining Lives: %d\n", lives);
    
    int revealed = 0;
    for(int i = 0; i < length; i++) {
        if(display[i] != '_') revealed++;
    }
    printf("Progress: %d/%d letters revealed\n", revealed, length);

}
