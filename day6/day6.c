#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <time.h>
#include <assert.h>
#include <stdbool.h>
#include <inttypes.h>

#define __STDC_FORMAT_MACROS
#define MAX_LINE_NUMBER 300
#define MAX_LINE_SIZE 300


void bad_input()
{
    printf("The input file isn't valid!\n");
    exit(-1);
}

bool eol(char c) {return !c || c == '\n' || c == '\r';}


int main(int argc, char**argv)
{
    // file parsing
    if(argc<2) bad_input(); // exit execution

    FILE* input_file = fopen(argv[1], "r");
    if(!input_file) bad_input(); // exit execution

    char input[MAX_LINE_NUMBER][MAX_LINE_SIZE];
    int line_nb = 0;

    while(line_nb<1000 && fgets(input[line_nb], MAX_LINE_SIZE, input_file)) {
		line_nb++;
	};

    fclose(input_file);

    clock_t start_point = clock();

    unsigned long long int output1 = 0, output2 = 0;

    char* ptr = input[0] + 11;
    
    int times[4];
    unsigned long long int distances[4];
    int race = 0;
    int num_eol = 0;

    while (num_eol < 2) {
        if (num_eol == 0) {
            times[race] = strtoll(ptr, &ptr, 10);
            ptr++;
            race++;
            // printf("times[race]= %i \n", times[race]);
            if (eol(*ptr)) {
                num_eol++;
                race = 0;
                ptr = input[1] + 11;
            } 
        };
        
        if (num_eol == 1) {
            // printf("*ptr= %c \n", *ptr);
            distances[race] = strtoll(ptr, &ptr, 10);
            ptr++;
            race++;
            // printf("distances[race]= %i \n", distances[race]);
            if (eol(*ptr)) {
                num_eol++;
                race = 0;
            } 
        }
    };

    for (int i = 0; i < 4; i++) {
        int num_ways = 0;
        // printf("distance: %i, time: %i\n",distances[i], times[i]);
        for (int j = 1; j < times[i]; j++) {
            long long int x = distances[i] - (j * (times[i] - j));
            if (x < 0) {
                num_ways++;
                // printf("num_ways=%i because pressing for %i (gets speed %i), and distance %i is achieved in remaining time %i\n",
                //     num_ways, j, j, distances[i], times[i]-j);
            }
        }
        if (output1 < 1) output1 = num_ways;
        else output1 = output1 * num_ways;
    };

    clock_t end_point = clock();

    printf("PART 1 Output : %"PRIu64"\n", output1);
    printf("Time : %lf micro-seconds\n", (double)(end_point - start_point)/CLOCKS_PER_SEC*1000000.0);

    // PART 2

    start_point = clock();

    char s1[10];
    char s2[10];
    char s3[40];
    char s4[40];

    unsigned long long int actualTime, actualDistance;

    for (int i = 0; i < 4; i++) {
        // printf("Distances = %i, \n", distances[i]);
        sprintf(s1, "%i", distances[i]);
        strcat(s3, s1);
        // printf("Copied = %s \n", s3);

        // printf("Times = %i, \n", times[i]);
        sprintf(s2, "%i", times[i]);
        strcat(s4, s2);
        // printf("Copied = %s \n", s4);
    }
    // 215 1064 1505 1100
    actualDistance = atoll(s3);
    actualTime = atoll(s4);

    printf("actualDistance = %llu, actualTime = %llu\n",actualDistance, actualTime);

    for (unsigned long long int j = 1; j < actualTime; j++) {
        long long int x = actualDistance - (j * (actualTime - j));
        if (x < 0) {
            output2++;
            // printf("num_ways=%llu because pressing for %llu (gets speed %llu), and distance %llu is achieved in remaining time %llu\n",
            //     output2, j, j, actualDistance, actualTime-j);
        }
    };

    end_point = clock();

    printf("PART 2 Output : %"PRIu64"\n", output2);
    printf("Time : %lf micro-seconds\n", (double)(end_point - start_point)/CLOCKS_PER_SEC*1000000.0);

    return 0;
}