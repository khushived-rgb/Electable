/*
 * sort_code.c
 * Impelments sorting of ocuse arrays by course_code using a selection of sort approaches
 * Author: Anshika Patel
 * Date: 2025-12-03
 * Version: v2.0.0
*/

#include <stddef.h>
#include <string.h>
#include "../include/filter.h"
#include "../include/sort.h"

/*
 * compare_course_code
 * compates the course_code of two elements in an array
 * Parameters:
 * 		- courses: array of courses
 * 		- i: index of the first element to compare
 * 		- j: index of the second element to compare
 * 		- ascending: 1 for ascending order; 0 for descending order
 * Return
 * 		- negative if courses[i] should come before courses[j]
 * 		- positive if courses[i] should come before courses[j]
*/
static int compare_course_code(Course courses[], int i, int j, int ascending){
	int cmp = strcmp(courses[i].course_code, courses[j].course_code);
	if (cmp < 0){
		if (ascending){
			return -1;
		} else {
			return 1;
		}
	}

	return 0;
}

/*
 * sort_by_course_code
 * sorts the given array by course by the course_code filed (lexicographically)
 * Parameters:
 * 		- course: array of course to sort
 * 		- count: number of element in the array
 * 		- ascending: 1 for ascending order;  for descending order
 *
*/
void sort_by_course_code(Course courses[], int count, int ascending){
	if (courses == NULL || count <= 1){
		return;
	}

	for (int i = 0; i < count -1; i++){
		int bestIndex = i;

		for (int j = i+1; j < count; j++){
			if (compare_course_code(courses, j, bestIndex, ascending) < 0){
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