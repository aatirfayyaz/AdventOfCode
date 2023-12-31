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

enum handTypes {
    fiveOfAKind,
    fourOfAKind,
    fullHouse,
    threeOfAKind,
    twoPair,
    onePair,
    highCard
};

struct game {
    char hand[5];
    int bid;
    enum handTypes handType;
    int rank;
};

enum handTypes getHandType(char *hand[5]) {
    char seen[13] = {0};
    for (int i = 0; i < 5; i++) {
        
    }
};

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

    while(line_nb < 1000 && fgets(input[line_nb], MAX_LINE_SIZE, input_file)) {
		line_nb++;
	};

    printf("Line numbers = %i (check against games array)\n", line_nb);
    fclose(input_file);

    struct game games[5];

    for (int i = 0; i < line_nb; i++) {
        char *ptr = input[i];
        strncpy(games[i].hand, ptr, 5);
        games[i].rank = 0;
        games[i].handType = getHandType(games[i].hand);
        games[i].bid = strtol(ptr + 6, &ptr, 10);

        printf("hand = %s, bid = %i, handType = %i, rank = %i\n", games[i].hand, games[i].bid, games[i].handType, games[i].rank);
    };

    return(0);

};