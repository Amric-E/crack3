#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "md5.h"

#if __has_include("fileutil.h")
#include "fileutil.h"
#endif

#define PASS_LEN 50     // Maximum length any password will be.
#define HASH_LEN 33     // Length of hash plus one for null.

int compareStrings(const void *a, const void *b) {
    return strcmp((const char *)a, (const char *)b);
}

int main(int argc, char *argv[])
{
    if (argc < 3) 
    {
        printf("Usage: %s hash_file dictionary_file\n", argv[0]);
        exit(1);
    }

    // Declare hashCount and load hashes
    int hashCount = 0;
    char (*hashes)[COLS] = loadFile2D(argv[1], &hashCount);  // argv[1] is the hash file

    if (!hashes) {
        fprintf(stderr, "Failed to load hashes from file.\n");
        return 1;
    }

    // Optional: Print to verify
    for (int i = 0; i < hashCount; i++) {
        printf("Hash %d: %s\n", i, hashes[i]);
    }

    
    // CHALLENGE1 
    qsort(hashes, hashCount, COLS, compareStrings);

    // Open the password file for reading
    FILE *dict = fopen(argv[2], "r");
    if (!dict) {
        perror("Error opening dictionary file");
        return 1;
    }

    // Decalared Vars
    char plaintext[PASS_LEN]; 
    char password[PASS_LEN];
    char hash[HASH_LEN];
    int foundCount = 0;

    // For each password in the dictionary
    while (fgets(password, PASS_LEN, dict)) {
        password[strcspn(password, "\n")] = '\0';  

        char *hash = md5(password, strlen(password));  

        char *found = exactMatchSearch2D(hash, hashes, hashCount);  

        if (found) {
            printf("Match found: %s = %s\n", hash, password);
            foundCount++;
        }
    }


    // close
    fclose(dict);

    printf("Total hashes matched: %d\n", foundCount);

    return 0;
}
