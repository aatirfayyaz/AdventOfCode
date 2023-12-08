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

    // Read the content of the file, line by line
    while(fgets(buffer, 128, fptr)) {
        
        // printf("Currently reading: %s\n", buffer);
        int size = strlen(buffer);
        int i = 0;
        char firstNumber, lastNumber;

        while (i < size){

            if(isdigit(buffer[i])) {
                firstNumber = buffer[i];
                // printf("First number is %c\n", firstNumber);
                break;
            }
            
            i += 1;
        }

        i = size;

        while (i >= 0) {

            if(isdigit(buffer[i])) {
                lastNumber = buffer[i];
                // printf("Last number is %c\n", lastNumber);
                
                // printf("First and last numbers are %c %c\n", firstNumber, lastNumber);
                int subtotal;
                subtotal = (firstNumber - 48) *10 + (lastNumber - 48);
                // printf("SubTotal = %d\n", subtotal);
                total += subtotal;
                // printf("Total = %d\n", total);

                break;
            }
            
            i -= 1;
            
        };

    };

    printf("Total = %d\n", total);

    // Close the file
    fclose(fptr);

    return 0;
}