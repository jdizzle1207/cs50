/**
 * initials.c
 *
 * Andrew Siplas
 * sippy87@gmail.com
 *
 * Prompts user for their name and outputs their initials in uppercase
 * with no spaces or periods, followed by newline.
 *
 * Program assumes input contains only letters plus singles spaces
 * between words
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void printCap(char);

int main (int argc, char* argv[])
{
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

	char* inputPtr = input;
	// print first initial as there won't be a leading space
	// to detect in the loop below
	printCap(*inputPtr);

	// loop through until null terminator is reached
	while (*inputPtr != '\0')
	{
		// if we encounter a space, print the next character in caps
		if (inputPtr[0] == ' ') printCap(*++inputPtr);
		// else just increment for next iteration
		else inputPtr++;
	}

	// free input buffer
	free (input);

	// print newline and return
	printf("\n");
	return 0;
}

/**
 * print character, converting to uppercase first if found to be lowercase
 */

void printCap(char character)
{
	if ( character >= 'a' && character <= 'z') character -= 32;
	printf("%c",character);
}
