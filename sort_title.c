/*
 * sort_title.c
 * Implements sorting of course arrays by the titel field using a selection sort approach
 * Author: Anshika Patel
 * Date: 2025-12-03
 * version: v2.0.0
*/

#include <stddef.h>
#include <string.h>
#include "../include/filter.h"
#include "../include/sort.h"

/*
 * compare_course_title
 * lexicographically compates titles at indices i and j
 * paramters
 * 		- courses: arrays of course
 * 		- i: index of the first element to compare
 * 		- j: index of the second element to compare
 * 		- ascending: 1 for ascending order; 0 for descending order
 * Returns:
 * 		- negative int if courses[i] should come before courses[j]
 * 		- positive int if courses[i] should come after courses[j]
 * 		- 0 if equal rating
*/
static int compare_course_title(Course courses[], int i, int j, int ascending){
	int cmp = strcmp(courses[i].title, courses[j].title);

	if (cmp < 0){
		if (ascending){
			return -1;
		} else {
			return 1;
		}
	}

	if (cmp > 0) {
		if (ascending){
			return 1;
		} else {
			return -1;
		}
	}

	return 0;
}

/*
 * sort_by_title
 * sorts course array by title using selection sort
 * Parameters
 * 		- courses: arrays of course
 * 		- count: number of elements
 * 		- ascending: 1 for ascending order; 0 for descending order
*/
void sort_by_title(Course courses[], int count, int ascending){
	if (courses == NULL || count <= 1){
		return;
	}

	for (int i = 0; i < count -1; i++){
		int bestIndex = i;

		for (int j = i+1; j < count; j++){
			if (compare_course_title(courses, j, bestIndex, ascending) < 0){
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