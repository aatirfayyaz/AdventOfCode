#include <stdio.h>
#include <string.h>
#include <ctype.h>


void setMaps(char *buffer, int *arr1, int *arr2) {

    int k = 0;
    int tmp[3] = {0};

    for (int j = 0; j < 256; j++) {

        if (k >= 3) { break; };
        if (buffer[j] == ' ') {
            k++;
        }
        else if (isdigit(buffer[j])) {
            tmp[k] = tmp[k] * 10 + (buffer[j] - '0');
        };

    };

    for (int j = 0; j < tmp[2]; j++) {
        
        arr2[(tmp[1]+j)] = arr1[tmp[0]+j];
        printf("arr[%i] changed to %i\n", tmp[1]+j, tmp[0]+j);
    };

};

int main() {

    FILE *fptr;

    const int beginSeedMap = 3;
    const int beginSoilMap = 7;
    const int beginFertMap = 12;
    const int beginWaterMap = 18;
    const int beginLightMap = 22;
    const int beginTempMap = 27;
    const int beginHumMap = 31;
    const int eof = 33;


    // Opening data file in read mode
    fptr = fopen("data.txt", "r");

    int least = 999999999;
    int seedsList[4] = {0};
    int seeds[100];
    int soil[100];
    int fert[100];
    int water[100];
    int light[100];
    int temp[100];
    int hum[100];
    int loc[100];

    for (int i = 0; i < 100; i++) {
        seeds[i] = i;
        soil[i] = i;
        fert[i] = i;
        water[i] = i;
        light[i] = i;
        temp[i] = i;
        hum[i] = i;
        loc[i] = i;
        // printf("soil[%i] = %i\n", i, soil[i]);
    };

    char buffer[256];
    // char fullFile[rows][columns];

    int i = 0;

    while(fgets(buffer, 256, fptr)) {
        
        if (i == 0) {
            
            int k = 0;
            
            for (int j = 0; j < 256; j++) {
                // printf("buffer[%i]: %c\n", j , buffer[j]);
                if (k >= 4) { break; };
                if (isdigit(buffer[j])) {
                    seedsList[k] = seedsList[k] * 10 + (buffer[j] - '0');
                    // printf("seeds[%i]: %i and buffer was [%c]\n", k , seeds[k], buffer[j]);
                    if (!isdigit(buffer[j-1])) {
                        continue;
                    }
                    else {
                        // printf("Incrementing k because isdigit(%c) = %i\n", buffer[j-1], isdigit(buffer[j-1]));
                        k++;
                    }
                }
                else {
                    // printf("Skipping char: %i\n", j);
                    continue;
                };

            };

        };

        if (i >= beginSeedMap   && i < beginSoilMap  - 2)   setMaps(buffer, seeds, soil);
        if (i >= beginSoilMap   && i < beginFertMap  - 2)   setMaps(buffer, soil, fert);
        if (i >= beginFertMap   && i < beginWaterMap - 2)   setMaps(buffer, fert, water);
        if (i >= beginWaterMap  && i < beginLightMap - 2)   setMaps(buffer, water, light);
        if (i >= beginLightMap  && i < beginTempMap  - 2)   setMaps(buffer, light, temp);
        if (i >= beginTempMap   && i < beginHumMap - 2)     setMaps(buffer, temp, hum);
        if (i >= beginHumMap    && i < eof)                 setMaps(buffer, hum, loc);
        

        i++;

    };

    for (int i = 0; i < 4; i++) {
        int tmp;
        tmp = loc[hum[temp[light[water[fert[soil[seedsList[i]]]]]]]];
        printf("Seed %i, soil %i, fertilizer %i, water %i, light %i, temperature %i, humidity %i, location %i\n",
            seedsList[i], seedsList[seeds[i]], fert[soil[seedsList[i]]], water[fert[soil[seedsList[i]]]], light[water[fert[soil[seedsList[i]]]]],
            temp[light[water[fert[soil[seedsList[i]]]]]], hum[temp[light[water[fert[soil[seedsList[i]]]]]]], tmp);

        if (tmp < least) {
            least = tmp;
        }
    };

    printf("Closest location at: %i\n", least);

    fclose(fptr);
    return 0;

};