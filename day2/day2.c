#include <stdio.h>
#include <string.h>
#include <ctype.h>

int main() {

    FILE *fptr;

    // Opening data file in read mode
    fptr = fopen("data.txt", "r");
    
    // Storing the content of the file in a buffer
    char buffer[256];
    int prevgameID = 0;
    int total = 0;

    // Array for spelled out numbers
    char *arr[] = { "red", "blue", "green"};

    // Reading the content of the file, line by line
    while(fgets(buffer, 256, fptr)) {

        int gameID;
        if ( isdigit(buffer[7]) ) {
            gameID = 100;
        } else if ( isdigit(buffer[6]) ) {
            gameID = ( buffer[5] - 48 ) * 10 + ( buffer[6] - 48 );
        } else {
            gameID = ( buffer[5] - 48 );
        };
        int maxRed = 0, maxBlue = 0, maxGreen = 0;
        
        // printf("Currently reading: %s\n", buffer);
        int size = strlen(buffer);

        for (int i = 0; i < 3; i++) {

            const char *tmp = buffer;

            while( (tmp = strstr(tmp, arr[i])) != NULL ) {
            
                char *result = strstr(tmp, arr[i]);
                
                if (result) {
                    
                    int position = tmp - buffer;
                    int cubes;
                    if ( isdigit(buffer[position - 3]) ) {
                        cubes = ( buffer[position - 3] - 48 ) * 10 + ( buffer[position - 2] - 48 );
                    } else {
                        cubes = ( buffer[position - 2] - 48 );
                    };

                    if (i == 0 && cubes > maxRed) { 
                        maxRed = cubes;
                    };
                    if (i == 1 && cubes > maxBlue) { 
                        maxBlue = cubes;
                    };
                    if (i == 2 && cubes > maxGreen) { 
                        maxGreen = cubes;
                    };

                    // printf("%s #: %i\n", arr[i] , cubes);
                    // printf("Game ID: %i\n", gameID);
                    // printf("Max: %i %i %i\n", maxRed, maxBlue, maxGreen);
                
                tmp += strlen(arr[i]);

                };

            };
        };

        if (maxRed <= 12 && maxGreen <= 13 && maxBlue <= 14) {
            if (prevgameID != gameID) {
                prevgameID = gameID;
                total += gameID;
                // printf("Adding gameID %i to total %i\n", gameID, total);
                };
        }
        else {
            // printf("Game ID %i does not qualify\n", gameID);
        };
                
        };

    printf("Total for gameIDs: %i\n", total);

    // Closing file
    fclose(fptr);
    
    
    return 0;

};