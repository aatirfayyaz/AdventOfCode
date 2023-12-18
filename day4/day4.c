#include <stdio.h>
#include <string.h>
#include <ctype.h>


int inWinningNums(int *winningNums, int n, int val) {
    for(int i = 0; i < n; i++) {
        if(winningNums[i] == val)
            return 1;
    }
    return 0;
};



int main() {

    FILE *fptr;
    const int rows = 187;
    const int columns = 116;
    const int firstNum = 10;
    const int lastNum = 39;

    // Opening data file in read mode
    fptr = fopen("data.txt", "r");

    int total = 0;
    int numCards[187];

    for (int i = 0; i < 187; i++) { 
        numCards[i] = 1;
    };

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
        
        int k = 0;
        int winningNums[10] = {0};
        int cardNums[25] = {0};

        for (int j = firstNum; j <= lastNum; j++) {
            if (k >= 10) { break; };
            if (fullFile[i][j] == ' ') {
                if (fullFile[i][j-1] == ' ') {
                    continue;
                }
                else {
                    k++;
                }
            }
            else {
                winningNums[k] = winningNums[k] * 10 + (fullFile[i][j] - '0');
                // printf("winningNums[%i] = %i\n", k, winningNums[k]);
            };
        };

        k = 0;

        for (int j = lastNum + 3; j < columns; j++) {
            if (k >= 25) { break; };
            if (fullFile[i][j] == ' ') {
                if (fullFile[i][j-1] == ' ') {
                    continue;
                }
                else {
                    k++;
                }
            }
            else {
                cardNums[k] = cardNums[k] * 10 + (fullFile[i][j] - '0');
                // printf("cardNums[%i] = %i\n", k, cardNums[k]);
            };
        };

        int match = 0;

        for (int j = 0; j < 25; j++) {

            if (inWinningNums(winningNums, 10, cardNums[j])) {
                // printf("Found %i in winningNums in row[%i]\n", cardNums[j], i);
                match++;
            };

        };

        for (int j = 0; j < match; j++) {

            numCards[i+j+1] += numCards[i];
            // printf("numCards[%i] = %i\n", i + j, numCards[i+j]);

        };
        
        total += numCards[i];
        printf("Match value at row[%i] = %i, and total now = %i\n", i, match, total);
    
    };

    printf("The total is: %i", total);

    fclose(fptr);
    return 0;
};
