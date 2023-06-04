CC = gcc
CFLAGS = -Wall -Wextra -std=c99

all: interpreter translator

interpreter: BrainEmoji.c
	$(CC) $(CFLAGS) -o interpreter BrainEmoji.c

translator: Translator.c
	$(CC) $(CFLAGS) -o translator Translator.c

.PHONY: clean
clean:
	rm -f interpreter translator
