#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int loadword(FILE *f, char word[100][100]) {
    int count = 0;
    while (fscanf(f, "%s", word[count]) == 1) {
        count++;
    }
    return count;
}

void printwords(char word[][50], int count) {
    for (int i = 0; i < count; i++) {
        printf("%s\n", words[i]);
    }
}

int main() {
    FILE *f = fopen("word.txt", "r");
    char words[100][100];
    int count;

    if (f == NULL) {
        printf("Cannot open file!\n");
        return 1;
    }

    
    count = loadword(f, word);

    printf("Word add: %d\n", count);

    
    printword(word, count);

    fclose(f);
    return 0;
}





   
