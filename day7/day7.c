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
#define MAX_LINE_SIZE 15

enum handTypes {
    fiveOfAKind = 0,
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

void getHandTypes(struct game *game) {
    char unique[5]; //Change based on line nb
    int counted = 0;
    int maxCount = 0;

    for (int i = 0; i < 5; i++) {
        bool already_counted = false;
        for (int j = 0; j < counted; j++) {
            if (game->hand[i] == unique[j]) already_counted = true;
        }

        if (already_counted) continue;

        int count = 0;
        for (int j = 0; j < 5; j++) {
            if (game->hand[i] == game->hand[j]) { 
                count++;
                if (count > maxCount) maxCount = count;
            } 
        }

        unique[counted] = game->hand[i];
        // printf("Char: %c has count = %i and saved at unique[%i] = %c & maxCount = %i\n", 
        //         game.hand[i], count, counted, game.hand[i], maxCount);
        counted++;

    }

    if (counted == 1) {
        // printf("fiveOfAKind: %c\n", unique[0]);
        game->handType = fiveOfAKind;
    }
    if (counted == 2) {
        if (maxCount == 3) {
            // printf("fullHouse: %c & %c\n", unique[0], unique[1]);
            game->handType = fullHouse;
        }
        else { 
            game->handType = fourOfAKind;
            // printf("fourOfAKind: %c & %c\n", unique[0], unique[1]);
        }
    }
    if (counted == 3) {
        if (maxCount == 3) {
            game->handType = threeOfAKind;
            // printf("threeOfAKind: %c, %c & %c\n", unique[0], unique[1], unique[2]);
        }
        else {
            game->handType = twoPair;
            // printf("twoPair: %c, %c & %c\n", unique[0], unique[1], unique[2]);

        }
    }
    if (counted == 4) {
        game->handType = onePair;
        // printf("onePair: %c, %c, %c & %c\n", unique[0], unique[1], unique[2], unique[3]);
    }
    if (counted == 5) {
        game->handType = highCard;
        // printf("highCard: %c, %c, %c, %c & %c\n", unique[0], unique[1], unique[2], unique[3], unique[4]);
    }

};


void rankHands(struct game *game) {

}

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
        getHandTypes(&games[i]);
        games[i].rank = 0;
        games[i].bid = strtol(ptr + 6, &ptr, 10);

        printf("hand = %s, bid = %i, handType = %i, rank = %i\n", games[i].hand, games[i].bid, games[i].handType, games[i].rank);
    };

    for (int i = 0; i < line_nb; i++) {
        
    }

    return(0);

};