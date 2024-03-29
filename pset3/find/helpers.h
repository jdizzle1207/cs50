/**
 * helpers.h
 *
 * Computer Science 50
 * Problem Set 3
 *
 * Helper functions for Problem Set 3.
 */
 
#include <cs50.h>

/**
 * Returns true if value is in array of n values, else false.
 */
bool search(int value, int values[], int n);

/**
 * Sorts array of n values.
 */
void sort(int values[], int n);

/**
 * Recursive binary search called from search() above. Returns
 * true if value is in array, else false.
 *
 * max is highest index we'll be checking.
*/
bool binsrch(int value, int array[], int min, int max);

