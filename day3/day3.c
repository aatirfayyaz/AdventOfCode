#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

const int rows = 12;
const int columns = 10;

int checkSymbol(int i, int j, int size, char fullFile[rows][columns]) {
    
    for (int x = 0; x < size; x++) {

        if (fullFile[i-1][j-1] != '.' && !(isdigit(fullFile[i-1][j-1])) && fullFile[i-1][j-1] != '\n' && fullFile[i-1][j-1] != '\0') {
            if (i == 0 || j == 0) {return 0;}
            else {
            printf("Symbol: %c @ i: %i & j: %i\n", fullFile[i-1][j-1], i, j);
            return 1;
            }
        }
        else if (fullFile[i-1][j] != '.' && !(isdigit(fullFile[i-1][j])) && fullFile[i-1][j] != '\n' && fullFile[i-1][j] != '\0') {
            if (i == 0) {return 0;}
            else {
            printf("Symbol: %c @ i: %i & j: %i\n", fullFile[i-1][j], i, j);
            return 1;
            }
        }
        else if (fullFile[i][j-1] != '.' && !(isdigit(fullFile[i][j-1])) && fullFile[i][j-1] != '\n' && fullFile[i][j-1] != '\0') {
            if (j == 0) {return 0;}
            else {
            printf("Symbol: %c @ i: %i & j: %i\n", fullFile[i][j-1], i, j);
            return 1;
            }
        }
        else if (fullFile[i+1][j-1] != '.' && !(isdigit(fullFile[i+1][j-1])) && fullFile[i+1][j-1] != '\n' && fullFile[i+1][j-1] != '\0') {
            if (i == rows || j == 0) {return 0;}
            else {
            printf("Symbol: %c @ i: %i & j: %i\n", fullFile[i+1][j-1], i, j);
            return 1;
            }
        }
        else if (fullFile[i+1][j] != '.' && !(isdigit(fullFile[i+1][j])) && fullFile[i+1][j] != '\n' && fullFile[i+1][j] != '\0') {
            if (i == rows) {return 0;}
            else {
            printf("Symbol: %c @ i: %i & j: %i\n", fullFile[i+1][j], i, j);
            return 1;
            }
        }
        else if (fullFile[i-1][j+1] != '.' && !(isdigit(fullFile[i-1][j+1])) && fullFile[i-1][j+1] != '\n' && fullFile[i-1][j+1] != '\0') {
            if (i == 0 || j == rows) {return 0;}
            else {
            printf("Symbol: %c @ i: %i & j: %i\n", fullFile[i-1][j+1], i, j);
            return 1;
            }
        }
        else if (fullFile[i+1][j+1] != '.' && !(isdigit(fullFile[i+1][j+1])) && fullFile[i+1][j+1] != '\n' && fullFile[i+1][j+1] != '\0') {
            if (i == rows || j == columns) {return 0;}
            else {
            printf("Symbol: %c @ i: %i & j: %i\n", fullFile[i+1][j+1], i, j);
            return 1;
            }
        }
        else if (fullFile[i][j+1] != '.' && !(isdigit(fullFile[i][j+1])) && fullFile[i][j+1] != '\n' && fullFile[i][j+1] != '\0') {
            if (j == columns) {return 0;}
            else {
            printf("Symbol: %c @ i: %i & j: %i\n", fullFile[i][j+1], i, j);
            return 1;
            }
        }
        
        i++;
        j++;

    };
    
    return 0;

};

int main(int argc, char **argv) {

    FILE *fptr;

    // Opening data file in read mode
    fptr = fopen("data.txt", "r");


    // char buffer[columns];
    char fullFile[rows][columns];


    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < columns; j++) {
            if (fscanf(fptr, "%c", &fullFile[i][j])) {
                fprintf(stderr, "Error reading data from file\n");
            };
        };
    };

    int partNum = 0;
    int total = 0;

    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < columns; j++) {
            printf("%c\n", fullFile[i][j]);
            if (isdigit(fullFile[i][j]) && isdigit(fullFile[i][j+1]) && isdigit(fullFile[i][j+2])) {
                partNum = (fullFile[i][j] - 48) * 100 + (fullFile[i][j+1] - 48) * 10 + (fullFile[i][j+2] - 48);
                if(checkSymbol(i, j, 3, fullFile)) {
                    total += partNum;
                };
                j += 2;
            } else if (isdigit(fullFile[i][j]) && isdigit(fullFile[i][j+1])) {
                partNum = (fullFile[i][j] - 48) * 10 + (fullFile[i][j+1] - 48);
                if(checkSymbol(i, j, 2, fullFile)) {
                    total += partNum;
                };
                j += 1;
            } else if (fullFile[i][j] > 48 && fullFile[i][j] != '.') {
                // printf("%c\n", fullFile[i][j]);
                partNum = (fullFile[i][j] - 48);
                if(checkSymbol(i, j, 1, fullFile)) {
                    total += partNum;
                };
            } else {
                partNum = 0;
                continue;
            };

            printf("partNum: %i\n", partNum);
            printf("Subtotal: %i", total);

        };

    };

    printf("Total parts near symbols: %i", total);
    fclose(fptr);

    return 0;

};