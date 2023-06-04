/**
 * BrainEmoji interpreter   
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TAPE_SIZE 30000

void interpretBrainEmoji(const char *code) {
    unsigned char tape[TAPE_SIZE] = {0};
    int ptr = 0;
    int loop_start_indices[TAPE_SIZE];
    int loop_count = 0;

    size_t code_len = strlen(code);
    for (size_t i = 0; i < code_len; i++) {
        const char *command = code + i;

        if (strncmp(command, "👉", 4) == 0) {
            ptr++;
        } else if (strncmp(command, "👈", 4) == 0) {
            ptr--;
        } else if (strncmp(command, "👍", 4) == 0) {
            tape[ptr]++;
        } else if (strncmp(command, "👎", 4) == 0) {
            tape[ptr]--;
        } else if (strncmp(command, "🫵", 4) == 0) {
            putchar(tape[ptr]);
        } else if (strncmp(command, "✍️", 4) == 0) {
            tape[ptr] = getchar();
            putchar(tape[ptr]);
        } else if (strncmp(command, "🫱", 4) == 0) {
            if (tape[ptr] == 0) {
                int loop_level = 1;
                while (loop_level > 0) {
                    i += 4;
                    command = code + i;
                    if (strncmp(command, "🫱", 4) == 0) {
                        loop_level++;
                    } else if (strncmp(command, "🫲", 4) == 0) {
                        loop_level--;
                    }
                }
            } else {
                loop_start_indices[loop_count] = i;
                loop_count++;
            }
        } else if (strncmp(command, "🫲", 4) == 0) {
            if (tape[ptr] != 0) {
                i = loop_start_indices[loop_count - 1] - 4;
            } else {
                loop_count--;
            }
        }
    }
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("Usage: %s <filename>\n", argv[0]);
        return 1;
    }

    FILE *file = fopen(argv[1], "r");
    if (!file) {
        printf("Error opening file '%s'\n", argv[1]);
        return 1;
    }

    fseek(file, 0, SEEK_END);
    long file_size = ftell(file);
    rewind(file);
    char *code = (char *)malloc(file_size + 1);
    fread(code, 1, file_size, file);
    fclose(file);
    code[file_size] = '\0';

    interpretBrainEmoji(code);

    free(code);

    return 0;
}
