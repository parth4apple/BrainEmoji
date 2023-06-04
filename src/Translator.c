/**
 * Takes a BrainFuck file as a command line argument and generates a new file in BrainEmoji
 * Note that characters besides the ones in the BrainEmoji syntax are ignored in this transpilation
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

const char* mapping[256] = {
    ['>'] = "👉",
    ['<'] = "👈",
    ['+'] = "👍",
    ['-'] = "👎",
    ['.'] = "🫵",
    [','] = "✍️",
    ['['] = "🫱",
    [']'] = "🫲"
};

int main(int argc, char *argv[]) {
    if (argc < 2) {
        printf("Usage: ./translator <brainfuck_file>\n");
        return 1;
    }

    FILE *inputFile = fopen(argv[1], "r");
    if (inputFile == NULL) {
        printf("Error opening file.\n");
        return 1;
    }

    char* inputFileName = argv[1];

    char* dotPtr = strrchr(inputFileName, '.');
    if (dotPtr == NULL) {
        printf("Invalid input file format. File name must have an extension.\n");
        return 1;
    }

    *dotPtr = '\0';
    char outputFileName[100];
    sprintf(outputFileName, "%s.be", inputFileName);
    
    FILE *outputFile = fopen(outputFileName, "w");
    if (outputFile == NULL) {
        printf("Error creating output file.\n");
        fclose(inputFile);
        return 1;
    }

    int ch;
    while ((ch = fgetc(inputFile)) != EOF) {
        const char* brainEmoji = mapping[ch];
        if (brainEmoji == NULL) {
            continue;
        }
        fputs(brainEmoji, outputFile);
    }

    fclose(inputFile);
    fclose(outputFile);

    printf("Conversion successful. Output file: %s\n", outputFileName);

    return 0;
}
