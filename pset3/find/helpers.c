/**
 * helpers.c
 *
 * Computer Science 50
 * Problem Set 3
 *
 * Helper functions for Problem Set 3.
 */
#include <cs50.h>
#include <stdio.h>
#include "helpers.h"

//prototypes
bool binsrch(int value, int array[], int min, int max);


/**
 * Returns true if value is in array of n values, else false.
 */
bool search(int value, int values[], int n)
{
	// call my recursive binary search
	return binsrch(value, values, 0, n);
}

/**
 * Sorts array of n values.
 */
void sort(int values[], int n)
{
	// for each item in the array
	for (int i = 0; i < n; i++)
	{
		// compare it to every other item after it
		for (int j = i+1; j < n; j++)
		{
			// swap if value > than the one after it
			if (values[i] > values[j])
			{
				int tmp = values[i];
				values[i] = values[j];
				values[j] = tmp;
			}
		}
	}
}

/**
 * Recursive binary search called from search() above. Returns
 * true if value is in array, else false.
 *
 * max is highest index we'll be checking.
 */
bool binsrch(int value, int array[], int min, int max)
{
	// if we've overlapped, it can't be here and we might segfault if we look
	if ( min > max ) return false;

	// find midpoint (of only those numbers we're actually looking at)
	int mid = ((max - min) / 2) + min;

	// compare to search key
	if ( array[mid] == value ) return true;

	// if not there, find out which half it *may* be in, then search that
	if ( array[mid] > value ) return binsrch(value, array, min, mid-1);
	if ( array[mid] < value ) return binsrch(value, array, mid+1, max);

	return false;
}

