#ifndef PLAYER_H_INCLUDED
#define PLAYER_H_INCLUDED


void getPlayerName(char *name, int maxLength); // To get the player name for our input :D
                                                    
void savePlayerScore(const char *playerName, int score);  // To save score to file 

void displayHighScores(); 

int loadWordsFromFile(const char *filename, const char *wordList[], int *wordCount); 


void freeWordList(const char *wordList[], int wordCount); // THis frees memory for word list

#endif // PLAYER_H_INCLUDED
