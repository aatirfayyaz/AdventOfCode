#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

const int rows = 140;
const int columns = 140;

int isValid(int row, int col, int rows, int columns) {
    return row >= 0 && row < rows && col >= 0 && col < columns;
}

int checkSymbol(int i, int j, int size, char fullFile[rows][columns]) {
    for (int x = 0; x < size; x++) {
        // printf("Parameters are i:%i, j:%i, size:%i\n", i, j, size);
        for (int r = i - 1; r <= i + 1; ++r) {
            for (int c = j - 1; c <= j + 1; ++c) {
                if (isValid(r, c, rows, columns)) {
                    // printf("Testing %c for size %i of %i at r: %i, c: %i\n", fullFile[r][c], x, size, r, c);
                    if (fullFile[r][c] != '.' && !isdigit(fullFile[r][c]) && fullFile[r][c] != '\0') {
                        // printf("Found a symbol @ r:%i and c:%i", r, c);
                        return 1;
                    };
                }
                else {
                    continue;
                };
            };
        };
        j++;
    };

    return 0;

};

int findNums(int row, int col, char fullFile[rows][columns]){
    if (isdigit(fullFile[row][col - 1])){
        if (isdigit(fullFile[row][col - 2])){
            return ((fullFile[row][col - 2] - 48) * 100 + (fullFile[row][col - 1] - 48) * 10 + (fullFile[row][col] - 48));
        }
        else if (isdigit(fullFile[row][col + 1])) {
            return ((fullFile[row][col - 1] - 48) * 100 + (fullFile[row][col] - 48) * 10 + (fullFile[row][col + 1] - 48));
        }
        else {
            return ((fullFile[row][col - 1] - 48) * 10 + (fullFile[row][col] - 48));
        }
    }
    else if (isdigit(fullFile[row][col + 1])){
        if (isdigit(fullFile[row][col + 2])){
            return ((fullFile[row][col] - 48) * 100 + (fullFile[row][col + 1] - 48) * 10 + (fullFile[row][col + 2] - 48));
        }
        else {
            return ((fullFile[row][col] - 48) * 10 + (fullFile[row][col + 1] - 48));
        }
    }
    else {
        return (fullFile[row][col] - 48);
    }
};

int checkDigit(int i, int j, char fullFile[rows][columns]) {
    int partNum;
    int gearRatio = 0;
    int foundOne = 0;
    for (int r = i - 1; r <= i + 1; ++r) {
        for (int c = j - 1; c <= j + 1; ++c) {
            if (isValid(r, c, rows, columns)) {
                if (isdigit(fullFile[r][c])) {
                    partNum = findNums(r, c, fullFile);
                    // printf("partNum = %i\n", partNum);
                    if (foundOne && gearRatio != partNum) {
                        // printf("gearRatio = %i\n", gearRatio*partNum);
                        return gearRatio *= partNum;
                    }
                    else {
                        gearRatio = partNum;
                        foundOne++;
                    };
                };
            }
            else {
                continue;
            };
        };
    };
    return 0;
};

int main(int argc, char **argv) {

    FILE *fptr;

    // Opening data file in read mode
    fptr = fopen("data.txt", "r");


    // char buffer[columns];
    char fullFile[rows][columns];


    for (int i = 0; i <= rows; i++) {
        for (int j = 0; j <= columns; j++) {
            if (fscanf(fptr, "%c", &fullFile[i][j])) {
                // fprintf(stderr, "Error reading data from file\n");
            };
        };
    };

    int partNum = 0;
    int total = 0;


    // Part 1 code
    //
    // for (int i = 0; i < rows; i++) {
    //     for (int j = 0; j < columns; j++) {
    //         // printf("Checking %c\n", fullFile[i][j]);
    //         if (isdigit(fullFile[i][j]) && isdigit(fullFile[i][j+1]) && isdigit(fullFile[i][j+2])) {
    //             partNum = (fullFile[i][j] - 48) * 100 + (fullFile[i][j+1] - 48) * 10 + (fullFile[i][j+2] - 48);
    //             // printf("Partnum: %i\n", partNum);
    //             if(checkSymbol(i, j, 3, fullFile)) {
    //                 total += partNum;
    //                 // printf("Added partNum: %i to total: %i\n", partNum, total);
    //             };
    //             j += 2;
    //         } else if (isdigit(fullFile[i][j]) && isdigit(fullFile[i][j+1])) {
    //             partNum = (fullFile[i][j] - 48) * 10 + (fullFile[i][j+1] - 48);
    //             // printf("Partnum: %i\n", partNum);
    //             if(checkSymbol(i, j, 2, fullFile)) {
    //                 total += partNum;
    //                 // printf("Added partNum: %i to total: %i\n", partNum, total);
    //             };
    //             j += 1;
    //         } else if (isdigit(fullFile[i][j])) {
    //             // printf("%c\n", fullFile[i][j]);
    //             partNum = (fullFile[i][j] - 48);
    //             // printf("Partnum: %i\n", partNum);
    //             if(checkSymbol(i, j, 1, fullFile)) {
    //                 total += partNum;
    //                 // printf("Added partNum: %i to total: %i\n", partNum, total);
    //             };
    //         } else {
    //             partNum = 0;
    //             continue;
    //         };

    //         // printf("partNum: %i", partNum);
    //         // printf(" Subtotal: %i\n", total);

    //     };

    // };

    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < columns; j++) {

            if (fullFile[i][j] == '*') {
                // printf("Found a * at i: %i, j: %i\n", i, j);
                printf("total: %i\n", checkDigit(i, j, fullFile));
                total += checkDigit(i, j, fullFile);
            };
        };
    };

    printf("Total parts near symbols: %i", total);
    fclose(fptr);

    return 0;

};