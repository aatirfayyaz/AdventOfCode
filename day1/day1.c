#include <stdio.h>
#include <string.h>
#include <ctype.h>

int main() {

    FILE *fptr;

    // Open a file in read mode
    fptr = fopen("data.txt", "r");
    
    // Store the content of the file in a buffer
    char buffer[128];
    int total = 0;

    // Array for spelled out numbers
    char *arr[] = { "one", "two", "three", "four", "five", "six", "seven", "eight", "nine" };

    // Read the content of the file, line by line
    while(fgets(buffer, 128, fptr)) {
        
        // printf("Currently reading: %s\n", buffer);
        int size = strlen(buffer);
        int i = 0;
        int firstPosition = size;
        int lastPosition = 0;
        int firstNumber, lastNumber;

        for (int i = 0; i < 9 ; i++) {
            
            char *result = strstr(buffer, arr[i]);
            
            if (result) {
                
                // printf("Found a %s\n", arr[i]);
                int position = result - buffer;
                int substringLength = size - position;

                // printf("position %i\n", position);
                if (position < firstPosition) {
                    firstPosition = position;
                    firstNumber = i + 1;
                }
                if (position > lastPosition) {
                    lastPosition = position;
                    lastNumber = i + 1;
                }
            
                // printf("Lowest number found to be %i @ %i, and highest found to be %i @ %i\n", firstNumber, firstPosition, lastNumber, lastPosition);

            };
                        
        };

        while (i < size) {

            if(isdigit(buffer[i])) {
                
                if (i < firstPosition) {
                    firstPosition = i;
                    firstNumber = buffer[i] - 48;
                    // printf("Lowest index position found to be %i, and highest found to be %i\n", firstPosition, lastPosition);
                };

                if (i > lastPosition) {
                    lastPosition = i;
                    lastNumber = buffer[i] - 48;
                    // printf("Lowest index position found to be %i, and highest found to be %i\n", firstPosition, lastPosition);
                };
                
                // printf("First number is %c\n", firstNumber);
            };
            
            i += 1;
        };

        printf("First number found to be %i @ %i, and last found to be %i @ %i\n", firstNumber, firstPosition, lastNumber, lastPosition);

        // i = size;

        // while (i >= 0) {

        //     if(isdigit(buffer[i])) {
        //         lastNumber = buffer[i];
        //         // printf("Last number is %c\n", lastNumber);
                
        //         // printf("First and last numbers are %c %c\n", firstNumber, lastNumber);
        //         int subtotal;
        //         subtotal = (firstNumber - 48) *10 + (lastNumber - 48);
        //         // printf("SubTotal = %d\n", subtotal);
        //         total += subtotal;
        //         // printf("Total = %d\n", total);

        //         break;
        //     };
            
        //     i -= 1;

        // };

    };

    printf("Total = %d\n", total);

    // Close the file
    fclose(fptr);

    return 0;
}