/*
 * sort_rating.c
 * Implements sorting of course arrays by the rating field using selection sort
 * Author: Anshika Patel
 * Date: 2025-12-03
 * version: v2.0.0
*/

#include <stddef.h>
#include "../include/filter.h"
#include "../include/sort.h"

/*
 * compare_course_rating
 * compares rating of two elements
 * Parameters:
 * 		- courses: arrays of courses
 * 		- i: index of the first element to compare
 * 		- j: index of the second element to compare
 * 		- ascending: 1 for ascending order; 0 for descending order
 * returns:
 * 		- negative int if courses[i] should come before courses[j]
 * 		- positive int if courses[i] should come after courses[j]
 * 		- 0 if equal rating
*/
static int compare_course_rating(Course courses[], int i, int j, int ascending){
	if (courses[i].rating < courses[j].rating){
		if (ascending){
			return -1;
		} else {
			return 1;
		}
	}

	if (courses[i].rating > courses[j].rating){
		if (ascending){
			return 1;
		} else {
			return -1;
		}
	}

	return 0;
}

/*
 * sort_by_rating
 * sorts the array of course by rating using selection sort
 * Parameters
 * 		- courses: arrays of courses
 * 		- count: number of elements
 * 		- ascending: 1 for ascending order; 0 for descending order
*/
void sort_by_rating(Course courses[], int count, int ascending){
	if (courses == NULL || count <= 1){
		return;
	}

	for(int i = 0; i < count-1; i++){
		int bestIndex = i;

		for (int j = i+1; j<count; j++){
			if (compare_course_rating(courses, j, bestIndex, ascending)< 0){
				bestIndex = j;
			}
		}

		if (bestIndex != i){
			Course temp = courses[i];
			courses[i] = courses[bestIndex];
			courses[bestIndex] = temp;
		}

	}
}