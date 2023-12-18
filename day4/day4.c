#include <stdio.h>
#include <string.h>
#include <ctype.h>

int main() {

    FILE *fptr;
    const int rows = 5;
    const int columns = 48;

    // Opening data file in read mode
    fptr = fopen("data.txt", "r");
    
    // Storing the content of the file in a buffer
    char buffer[256];
    int prevgameID = 0;
    int total = 0;

    // Array for spelled out numbers
    char *arr[] = { "red", "blue", "green"};

    // char buffer[columns];
    char fullFile[rows][columns];


    for (int i = 0; i <= rows; i++) {
        for (int j = 0; j <= columns; j++) {
            if (fscanf(fptr, "%c", &fullFile[i][j])) {
                // fprintf(stderr, "Error reading data from file\n");
            };
        };
    };

    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < columns; j++) {

            printf("%c", fullFile[i][j]);

        };
    };


};
