#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "player.h"

void getPlayerName(char *name, int maxLength)
{
    fgets(name, maxLength, stdin);
    
    int i = 0;
    while (name[i] != '\0') {
        if (name[i] == '\n') {
            name[i] = '\0';
            break;
        }
        i++;
    }
    
    if (name[0] == '\0') {
        strcpy(name, "Player");
    }
}

void savePlayerScore(const char *playerName, int score)
{
    FILE *file = fopen("data/scores.txt", "a");
    if (file == NULL) {
        printf("Warning: Could not save score.\n");
        return;
    }
    
    fprintf(file, "%s:%d\n", playerName, score);
    fclose(file);
}

void displayHighScores()
{
    FILE *file = fopen("data/scores.txt", "r");
    if (file == NULL) {
        printf("No high scores yet.\n");
        return;
    }
    
    char names[100][50];
    int scores[100];
    int count = 0;
    
    while (count < 100 && fscanf(file, "%49[^:]:%d\n", names[count], &scores[count]) == 2) {
        count++;
    }
    fclose(file);
    
    int i, j;
    for (i = 0; i < count - 1; i++) {
        for (j = 0; j < count - i - 1; j++) {
            if (scores[j] < scores[j + 1]) {
                int temp = scores[j];
                scores[j] = scores[j + 1];
                scores[j + 1] = temp;
                
                char tempName[50];
                strcpy(tempName, names[j]);
                strcpy(names[j], names[j + 1]);
                strcpy(names[j + 1], tempName);
            }
        }
    }
    
    int limit = count;
    if (limit > 10) {
        limit = 10;
    }
    
    for (i = 0; i < limit; i++) {
        printf("%d. %s - %d points\n", i + 1, names[i], scores[i]);
    }
}

int loadWordsFromFile(const char *filename, const char *wordList[], int *wordCount)
{
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        return -1;
    }
    
    char buffer[100];
    *wordCount = 0;
    
    while (*wordCount < 50 && fgets(buffer, 100, file) != NULL) {
        int len = strlen(buffer);
        if (len > 0 && buffer[len - 1] == '\n') {
            buffer[len - 1] = '\0';
            len--;
        }
        
        if (len > 0) {
            char *word = (char*)malloc(len + 1);
            if (word == NULL) {
                continue;
            }
            
            int i;
            for (i = 0; i <= len; i++) {
                word[i] = tolower(buffer[i]);
            }
            
            wordList[*wordCount] = word;
            (*wordCount)++;
        }
    }
    
    fclose(file);
    return 0;
}

void freeWordList(const char *wordList[], int wordCount)
{
    int i;
    for (i = 0; i < wordCount; i++) {
        free((void*)wordList[i]);
    }
}
