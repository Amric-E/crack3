#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "fileutil.h"

// Defined 
#define MAX_LINES 1000
#define MAX_LINE_LEN 256 

// DIRECTIONS
// 2D array 
// For the 2D array,
// implement loadFile2D, substringSearch2D, and free2D.

// LoadFile2D
char (*loadFile2D(char *filename, int *size))[COLS] {
    FILE *in = fopen(filename, "r");
    if (!in) {
        perror("Error");
        exit(1);
    }

    // Allocate memory for 2D array
    char (*array)[COLS] = malloc(MAX_LINES * COLS);
    if (!array) {
        perror("Memory allocated failed");
        exit(1);
    }

    char buffer[COLS];
    *size = 0;

    // Read lines into array
    while (fgets(buffer, COLS, in) && *size < MAX_LINES) {
        buffer[strcspn(buffer, "\n")] = '\0';  // Trim newline
        strcpy(array[*size], buffer);
        (*size)++;
    }

    fclose(in);
    return array;
}

// SubstringSearch2D
char *substringSearch2D(char *target, char (*arr)[COLS], int size) {
    for (int i = 0; i < size; i++) {
        if (strstr(arr[i], target)) {
            return arr[i];
        }
    }
    return NULL;
}

// Free2D
void free2D(char (*arr)[COLS]) {
    free(arr);
}

// Added function for crack3
// ExactMatchSearch2D
char *exactMatchSearch2D(char *target, char (*arr)[COLS], int size) {
    for (int i = 0; i < size; i++) {
        if (strcmp(arr[i], target) == 0) {
            return arr[i];  // Found exact match
        }
    }
    return NULL;  // Not found
}
