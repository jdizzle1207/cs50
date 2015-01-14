/**
 * greedy.c
 *
 * Andrew Siplas
 * sippy87@gmail.com
 *
 * prompts user for change to give and displays the minimum
 * number of coins (quarters, dimes, nickels, pennies)
 * needed to be given as change
 */

#include <stdio.h>
#include <math.h>

int deduct (int*,int,int*);

int main (int argc, char* argv[])
{
// allocate buffer, etc.
int bufsz = 255;
char buffer[bufsz];
float input;
int change = 0;
// prompt user for input until we get float
printf ("O hai! ");
do
{
	printf ("How much change is owed?\n");
	fgets(buffer, bufsz, stdin);
} while (!sscanf(buffer,"%f",&input) || input <= 0);

// set balance to equal number of pennies to avoid float errors
int balance = (int)round(input*100);

// for each denomination (large to small) deduct until we can't any more
// keeping track of each coin to give via change variable
int denominations[] = {25, 10, 5, 1};
for (int i = 0; i < sizeof(denominations); i++)
{
while(deduct(&balance, denominations[i], &change));
}

printf ("%i\n",change);

return 0;

}

/**
 * deducts given number of pennies from balance of change to be given
 *
 * inputs are reference to balance, deduction to be taken, and ref to change
 *
 * returns true upon successful deduction
 * returns false and does not deduct if deduction would result in negative
 * balance
 */

int deduct (int* balance, int deduction, int* change)
{
if ((deduction <= *balance) && (*balance != 0))
{
	*change += 1;
	*balance -= deduction;
	return 1;
}
else return 0;
}
