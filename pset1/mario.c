/**
 * mario.c
 *
 * Andrew Siplas
 * sippy87@gmail.com
 *
 * prompts user for height and displays 'mario pyramid' in terminal
 */

#include <stdio.h>
#include <stdlib.h>

int main (int argc, char* argv[])
{

// allocate buffer for height and int to store it after parse
int bufsz = 255;
char buffer[bufsz];
int height;

// get user input height (keep trying until get -1 < int < 24)
do {
printf ("height: ");
// set invalid height if error or no characters read
if (fgets(buffer, bufsz, stdin) == '\0') height = -1;
// use scanf to pull out int while rejecting "foo", for example which
// would return 0 for no match
if (sscanf(buffer,"%i",&height) != 1) height = -1;
} while (height < 0 || height > 23);

// the max width is height + 1 so allocate char array plus null terminator
char output[height+1+1];
// null terminate the array
output[sizeof(output)-1] = '\0'; 

/**
 * fill array with appropriate spaces and hashes for line 1
 * hash preceded by (height-1) number of spaces (we make second hashmark
 * on the first iteration of 'flipme' below
 */

for (int i = 0; i < sizeof(output)-1; i++)
{
	(i < height-1) ? (output[i] = ' ') : (output[i] = '#');
}

/**
 * iterate over array and flip one char on each iteration as we print
 * we start second from the end because we put the fist has on
 * initialization above (its -3 below due to null terminator
 */

for (int flipme = sizeof(output)-3; flipme > -1; flipme--)
{
output[flipme] = '#';
printf("%s\n", output);
}

return 0;
}

