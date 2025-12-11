#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
    FILE *f = fopen("words.txt", "r");
    char words[100][50];
    int count = 0;

    if (f == NULL)
        {
        printf("Cannot open file!\n");
        return 1;
    }


    while (fscanf(f, "%s", words[count]) == 1)
    {
        count++;
    }

    printf("Word add: %d\n", count);


    for (int i = 0; i < count; i++)
    {
        printf("%s\n", words[i]);
    }

    fclose(f);
    return 0;
}


