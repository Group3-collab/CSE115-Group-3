#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "player.h"

// gets the player's name from input
void getPlayerName(char *name, int maxLength)
{
    // read input from user
    fgets(name, maxLength, stdin);
    
    // loop through to find newline character
    int i = 0;
    while (name[i] != '\0')
    {
        if (name[i] == '\n')
        {
            name[i] = '\0';  // replace newline with null terminator
            break;
        }
        i++;
    }
    
    // if the user didnt type anything, use default
    if (strlen(name) == 0)
    {
        strcpy(name, "Player");
    }
}

// saves the players score to a file
void savePlayerScore(const char *playerName, int score)
{
    // try to open the file in append mode
    FILE *file = fopen("data/scores.txt", "a");
    
    // check if it worked
    if (file == NULL)
    {
        printf("Could not save score.\n");  // error mesage
        return;
    }
    
    // write the name and score seperated by colon
    fprintf(file, "%s:%d\n", playerName, score);
    fclose(file);
}

// displays the top scores from the file
void displayHighScores()
{
    // open file for reading
    FILE *file = fopen("data/scores.txt", "r");
    
    // if file doesnt exist yet, no scores to show
    if (file == NULL)
    {
        printf("No scores yet.\n");
        return;
    }
    
    // temperary variables for reading each line
    char name[50];
    int score;
    
    // arrays to store all the scores we read
    char allNames[100][50];
    int allScores[100];
    int total = 0;
    
    // keep reading until we reach end of file or hit limit
    while (fscanf(file, "%[^:]:%d\n", name, &score) == 2)
    {
        strcpy(allNames[total], name);
        allScores[total] = score;
        total++;
        
        if (total >= 100)  // dont go over array size
            break;
    }
    
    fclose(file);
    
    // sort the scores from highest to lowest using bubble sort
    // we learned this algoritm in class
    for (int i = 0; i < total - 1; i++)
    {
        for (int j = 0; j < total - i - 1; j++)
        {
            // if current is less than next, swap them
            if (allScores[j] < allScores[j + 1])
            {
                // swap the scores
                int tempScore = allScores[j];
                allScores[j] = allScores[j + 1];
                allScores[j + 1] = tempScore;
                
                // also swap the correspnding names
                char tempName[50];
                strcpy(tempName, allNames[j]);
                strcpy(allNames[j], allNames[j + 1]);
                strcpy(allNames[j + 1], tempName);
            }
        }
    }
    
    // figure out how many to display (maximum 10)
    int show = total;
    if (show > 10)
        show = 10;
    
    // print the top scores
    for (int i = 0; i < show; i++)
    {
        printf("%d. %s - %d points\n", i + 1, allNames[i], allScores[i]);
    }
}

// loads words from the text file into memory
int loadWordsFromFile(const char *filename, const char *wordList[], int *wordCount)
{
    // try opening the file
    FILE *file = fopen(filename, "r");
    
    // if file doesnt exist return error code
    if (file == NULL)
    {
        return -1;
    }
    
    char line[100];  // buffer for each line
    *wordCount = 0;  // start counting from zero
    
    // read the file line by line
    while (fgets(line, 100, file) != NULL)
    {
        // get the lenght of current line
        int length = strlen(line);
        
        // remove newline charcter at end
        if (line[length - 1] == '\n')
        {
            line[length - 1] = '\0';
            length--;
        }
        
        // only process if line is not emtpy
        if (length > 0)
        {
            // allocate memory for this word
            char *newWord = (char *)malloc(length + 1);
            
            // check if malloc suceeded
            if (newWord != NULL)
            {
                // copy the word into allocated memroy
                strcpy(newWord, line);
                
                // convert evrything to lowercase
                for (int i = 0; i < length; i++)
                {
                    newWord[i] = tolower(newWord[i]);
                }
                
                // add to our list
                wordList[*wordCount] = newWord;
                (*wordCount)++;
            }
        }
        
        // stop if we reached maximum
        if (*wordCount >= 50)
            break;
    }
    
    fclose(file);
    return 0;  // sucess
}
