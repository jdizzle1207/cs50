/**
 * caesar.c
 *
 * Andrew Siplas
 * sippy87@gmail.com
 *
 * Takes non-negative int as (only!) command line parameter
 * Prompts user for input
 * Ciphers text utilizing command line parameter as key
 * Outputs ciphered text
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

int rotate (char, int);

int main (int argc, char* argv[])
{
	// variable to store key
	int key;

	/**
	 * input checking
	 */

	// if we don't receive 1 (and only 1) command line parameter
	// in addition to the program name that the shell populates,
	// and said parameter is not a non-negative int,
	// complain and return 1
	if (argc != 2)
	{
		printf("Program takes 1 argument, a non-negative int to be used as cipher key!\n");
		return 1;
	}
	else
	{
		key = atoi(argv[1]);
		if (key < 0)
		{
			printf("Key must be a non-negative integer!\n");
			return 1;
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

	for (int i = 0; i < strlen(input); i++)
	{
		// for lowercase 0 = 'a'
		if (islower(input[i]))
		{
			input[i] = rotate(input[i] - 'a',key) + 'a';
		}
		// for uppercase, 0 = 'A'
		else if (isupper(input[i]))
		{
			input[i] = rotate(input[i] - 'A',key) + 'A';
		}
	}

	/**
	 * print result
	 */

	printf("%s\n",input);

	return 0;
}

/**
 * takes an int as input and rotates it by key, wrapping after 26 back to start
 */
int rotate (char inchar, int key)
{
	return (inchar + key) % 26;
}
