#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
// #include <sys/types.h>
// #include <time.h>
// #include <assert.h>
// #include <inttypes.h>

#define __STDC_FORMAT_MACROS
#define LINE_NUMBER 1000
#define MAX_LINE_SIZE 15
#define HAND_SIZE 5

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
    char hand[HAND_SIZE];
    int bid;
    enum handTypes handType;
    int rank;
};

static void getHandTypes(struct game *game, int partTwo) {
    char unique[HAND_SIZE];
    int counted = 0;
    int maxCount = 0;
    int jokers = 0;

    for (int i = 0; i < HAND_SIZE; i++) {
        if (game->hand[i] == 'J' && partTwo) {
            jokers++;
            continue;
        }

        bool already_counted = false;
        for (int j = 0; j < counted; j++) {
            if (game->hand[i] == unique[j]) already_counted = true;
        }

        if (already_counted) continue;

        int count = 0;
        for (int j = 0; j < HAND_SIZE; j++) {
            if (game->hand[i] == game->hand[j]) { 
                count++;
                if (count > maxCount) maxCount = count;
            } 
        }

        unique[counted] = game->hand[i];
        counted++;
    }

    if (partTwo && jokers) {
        maxCount += jokers;
        // printf("Count = %i & maxCount = %i\n", counted, maxCount);
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

static int sortHands(const void *p, const void *q)
{
    const struct game* a = (const struct game*)p;
    const struct game* b = (const struct game*)q;
    if (a->handType < b->handType) return -1;
    if (a->handType > b->handType) return  1;
    if (a->rank > b->rank) return -1;
    if (a->rank < b->rank) return  1;
    return 0;
}


static int getVal(char card, int partTwo) {
    if (card <= '9')
        return card & 15;
    switch (card) {
        case 'T': return 10;
        case 'J': return (partTwo) ? 0 : 11;
        case 'Q': return 12;
        case 'K': return 13;
        case 'A': return 14;
    }
    return 0; 
}


static void rankHands(struct game *game, int partTwo) {
    game->rank = 0;
    for (int i = 0; i < HAND_SIZE; ++i) {
        const int val = getVal(game->hand[i], partTwo);
        game->rank = game->rank * 100 + val;  // ranking just based on integer value concatenation
        // printf("rank = %d, val = %d\n", game->rank, val);
    }
}

static void bad_input()
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

    char input[LINE_NUMBER][MAX_LINE_SIZE];
    int line_nb = 0;

    while(line_nb < 1000 && fgets(input[line_nb], MAX_LINE_SIZE, input_file)) {
		line_nb++;
	};

    const int partTwo = 1;

    // printf("Line numbers = %i (check against games array)\n", line_nb);
    fclose(input_file);

    struct game games[LINE_NUMBER];
    int fiveOfAKindRank=0, fourOfAKindRank=0, fullHouseRank=0, threeOfAKindRank=0, twoPairRank=0, onePairRank=0, highCardRank=0;

    for (int i = 0; i < line_nb; i++) {
        char *ptr = input[i];
        strncpy(games[i].hand, ptr, 5);
        getHandTypes(&games[i], partTwo);
        rankHands(&games[i], partTwo);
        games[i].bid = strtol(ptr + 6, &ptr, 10);
        // printf("hand = %s, bid = %i, handType = %i, rank = %i\n", games[i].hand, games[i].bid, games[i].handType, games[i].rank);
    };

    qsort(games, LINE_NUMBER, sizeof *games, sortHands);

    int score = 0;
    for (int i = 0; i < LINE_NUMBER; ++i)
        score += games[i].bid * (LINE_NUMBER - i);
    printf("Score = %d\n", score);

    return(0);
};