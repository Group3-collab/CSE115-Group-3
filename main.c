#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "game.h"
#include "player.h"

void main()
{
char word[20]="PROGRAMMING";
    char guess[26]="AEI";
    char show[20];
    int i,j,lives=4,len;
    
    len=strlen(word);
    
    for(i=0;i<len;i++){
        show[i]='_';
    }
    show[len]='\0';

    for(i=0;i<len;i++){
        for(j=0;j<strlen(guess);j++){
            if(word[i]==guess[j]){
                show[i]=word[i];
            }
        }
    }
    
    printf("\n");
    printf("  +---+\n");
    printf("  |   |\n");
    printf("  O   |\n");
    printf(" /|\\  |\n");
    if(lives>0)
        printf(" /     |\n");
    else
        printf(" / \\  |\n");
    printf("      |\n");
    printf("========\n");
    
    printf("\nHANGMAN\n");
    printf("Word: ");
    for(i=0;i<len;i++){
        printf("%c ",show[i]);
    }
    printf("\nGuessed: ");
    for(i=0;i<strlen(guess);i++){
        printf("%c ",guess[i]);
    }
    printf("\nLives: %d\n",lives);
}
