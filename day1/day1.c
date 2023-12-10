#include <stdio.h>
#include <string.h>
#include <ctype.h>

int main() {

    FILE *fptr;

    // Opening data file in read mode
    fptr = fopen("data.txt", "r");
    
    // Storing the content of the file in a buffer
    char buffer[128];
    int total = 0;

    // Array for spelled out numbers
    char *arr[] = { "one", "two", "three", "four", "five", "six", "seven", "eight", "nine" };

    // Reading the content of the file, line by line
    while(fgets(buffer, 128, fptr)) {
        
        // printf("Currently reading: %s\n", buffer);
        int size = strlen(buffer);
        int firstPosition = size;
        int lastPosition = 0;
        int firstNumber, lastNumber;

        // Looping through spelled out digits array     
        for (int i = 0; i < 9 ; i++) {
            
            const char *tmp = buffer;
            int tmpPos = 0;

            while( (tmp = strstr(tmp, arr[i])) != NULL ) {
            
                char *result = strstr(tmp, arr[i]);
                
                if (result) {
                    
                    // printf("Found a %s\n", arr[i]);
                    int position = tmp - buffer;
                    // int substringLength = size - position;

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
                
                tmp += strlen(arr[i]);

            };
                        
        };

        int i = 0;
        
        while (i <= size) {

            if(isdigit(buffer[i])) {
                
                if (i < firstPosition) {
                    firstPosition = i;
                    firstNumber = buffer[i] - 48;
                    printf("Lowest index position found to be %i with val: %i\n", firstPosition, firstNumber);
                };

                if (i >= lastPosition) {
                    lastPosition = i;
                    lastNumber = buffer[i] - 48;
                    printf("Highest index found to be %i with val: %i\n", lastPosition, lastNumber);
                };
                
                // printf("First number is %c\n", firstNumber);
            };
            
            i += 1;
        };

        int subtotal;
        subtotal = (firstNumber) * 10 + (lastNumber);
        
        total += subtotal;

        // printf("SubTotal = %i and RunningTotal = %i\n", subtotal, total);
        printf("For: %s First number = %i @ %i, and last = %i @ %i; so sub = %i & Total = %i\n", buffer, firstNumber, firstPosition, lastNumber, lastPosition, subtotal, total);

        };

    printf("Total = %d\n", total);

    // Closing file
    fclose(fptr);

    return 0;
}