/**
 * helpers.c
 *
 * Computer Science 50
 * Problem Set 3
 *
 * Helper functions for Problem Set 3.
 */
#include <cs50.h>

#include "helpers.h"

/**
 * Returns true if value is in array of n values, else false.
 */
bool search(int value, int values[], int n)
{
	// call my recursive binary search
	return binsrch(n, values, n);
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
	return;
}

/**
 * Recursive binary search called from search() above. Returns
 * true if value is in array, else false.
 *
 * max is highest index we'll be checking.
 */
bool binsrch(int value, int array[], int max)
{
	// if given what we want
	if (array[0] == value) return true;

	// if we didn't find it by the end
	if (array[0] == array[max]) return false;

	// get middle value
	int mid = sizeof(*array) / 2;

	// if middle value is what we want then say so
	if (array[mid] == value) return true;
	
	// if middle of array is greater than what we want search 1st 1/2
	if (array[mid] > value) binsrch(value,&array[0],mid-1);

	// else take 2nd half
	else binsrch(value,&array[mid],sizeof(&array[mid]));

	return false;
}

