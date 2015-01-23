/**
 * vigenere.c
 *
 * Andrew Siplas
 * sippy87@gmail.com
 *
 * Accepts one command line arg, a completely alphabetic key which
 * is used to encrypt text.
 *
 * Prompts user for text to encode.
 *
 * Encrypts only alphabetic text by rotating each letter a number of times
 * as determined by current character in key, where a=0, z=25.
 *
 * For next substitution, the following letter in key is utilized, and
 * wraps back to first character after reaching end.
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

int rotate (char, int);

int main (int argc, char* argv[])
{
	/**
	 * input checking
	 */

	// if we don't receive 1 (and only 1) command line parameter
	// in addition to the program name that the shell populates,
	// and said parameter is not entirely alphabetic,
	// complain and return 1
	if (argc != 2)
	{
		printf("Program takes 1 argument, an alphabetic string to used as cipher key!\n");
		return 1;
	}
	else
	{
		for (int i = 0; i < strlen(argv[1]); i++)
		{
			if (!isalpha(argv[1][i]))
			{
				printf("Key must be completely alphabetic!\n");
				return 1;
			}
		}
	}

	/*
	 * prompt user for name using a loop until newline is rec'd
	 */

	// allocate input buffer
	char* input = malloc(sizeof(char));
	// use this var to keep track of current offset
	int curPos = 0;
	do {
		// allocate space for char and receive it
		input = realloc(input, strlen(input) + sizeof(char));
		input[curPos] = getchar();
	// stop reading if the character rec'd is newline
	} while ( input[curPos++] != '\n');

	/**
	 * rotate each character if it's a letter
	 *
	 * uses the algorithm encrypted = (input + key) % 26
	 * where encrypted will be 0=a, 26=z so we'll have to
	 * handle the case ourselves 
	 */

	// to track position in key
	int keyPos = 0;
	for (int i = 0; i < strlen(input); i++)
	{
		// set the key to be the value of the current letter
		// in the cipher key where a=0 z=25, regardless of case
		int key = tolower(argv[1][keyPos]) - 'a';

		// for lowercase 0 = 'a'
		if (islower(input[i]))
		{
			input[i] = rotate(input[i] - 'a',key) + 'a';
			keyPos = (keyPos + 1) % strlen(argv[1]);
		}
		// for uppercase, 0 = 'A'
		else if (isupper(input[i]))
		{
			input[i] = rotate(input[i] - 'A',key) + 'A';
			keyPos = (keyPos + 1) % strlen(argv[1]);
		}
	}

	/**
	 * print result
	 */

	printf("%s",input);

	return 0;
}

/**
 * takes an int as input and rotates it by key, wrapping after 26 back to
 * start.
 */
int rotate (char inchar, int key)
{
	return (inchar + key) % 26;
}

