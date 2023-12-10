#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

int main(int argc, char **argv) {

    FILE *fptr;

    // Opening data file in read mode
    fptr = fopen("data.txt", "r");

    const int rows = 10;
    const int columns = 10;

    char buffer[columns];
    char fullFile[rows][columns];


    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < columns; j++) {
            if (fscanf(fptr, "%c", &fullFile[i][j]) != 1) {
                fprintf(stderr, "Error reading data from file\n");
            };
        };
    };

    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < columns; j++) {
            if ( !isdigit(fullFile[i][j]) && fullFile[i][j] != 46 && fullFile[i][j] != 10) {
                    if ( i > 0 && i < rows && j > 0 && j < columns) {
                        printf("From %i %i at i-1, j: %c\n", i, j, fullFile[i-1][j]);
                        printf("From %i %i at i+1, j: %c\n", i, j, fullFile[i+1][j]);
                        printf("From %i %i at i-1, j-1: %c\n", i, j, fullFile[i-1][j-1]);
                        printf("From %i %i at i+1, j-1: %c\n", i, j, fullFile[i+1][j-1]);
                        printf("From %i %i at i, j-1: %c\n", i, j, fullFile[i][j-1]);
                        printf("From %i %i at i, j+1: %c\n", i, j, fullFile[i][j+1]);
                        printf("From %i %i at i-1, j+1: %c\n", i, j, fullFile[i-1][j+1]);
                        printf("From %i %i at i+1, j+1: %c\n", i, j, fullFile[i+1][j+1]);

                    }
                    else if ( i == 0 && j > 0 && j < columns) {}
                    else if ( i == rows && j > 0 && j < columns) {}
                    else if ( i > 0 && i < rows && j == 0) {}
                    else if ( i > 0 && i < rows && j == columns) {}
                    else if ( i == 0 && j == 0 ) {}
                    else if ( i == 0 && j == columns) {}
                    else if ( i == rows && j == 0) {}
                    else if ( i == rows && j == columns) {}
                    else { printf("You've missed a case!"); }
            } 
        }
        
        // printf("\n");
    };

    fclose(fptr);

    return 0;

};