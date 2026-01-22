/*
 * sort_difficulty.c
 * Implements sorting of course arrays by the difficulty fieldusing selection sort
 * Auhor: Anshika Patel
 * Date: 2025-12-03
 * Version: v2.0.0
*/

#include <stddef.h>
#include "../include/filter.h"
#include "../include/sort.h"

/*
 * Compare_course_difficulty
 * compates difficulty of two elements (i and j index)
 * Paramters:
 *      - courses: arrays of course
 *      - i: index of the first element to compare
 *      - j: index of the second element to compate
 *      - ascending: 1 for ascending order; 0 for descending order
 * Returns:
 *      - negative int if courses[i] should come before courses[j]
 *      - positive if courses[i] should come after courses[j]
 *      - 0 if equal difficulty
*/
static int compare_course_difficulty(Course courses[], int i, int j, int ascending) {
    if (courses[i].difficulty < courses[j].difficulty) {
        return ascending ? -1 : 1;
    }
    if (courses[i].difficulty > courses[j].difficulty) {
        return ascending ? 1 : -1;
    }
    return 0;
}

/*
 * sort_by_difficulty
 * sorts the array of course by difficulty using selection sort
 * Parameters:
 *      - courses: arrays of courses to sort
 *      - count: number of elements
 *      - ascending: 1 for ascending order; 0 for descending order
*/
void sort_by_difficulty(Course courses[], int count, int ascending) {
    if (courses == NULL || count <= 1) {
        return;
    }
    for (int i = 0; i < count - 1; ++i) {
        int bestIndex = i;

        //find the best course for position
        for (int j = i + 1; j < count; ++j) {
            if (compare_course_difficulty(courses, j, bestIndex, ascending) < 0) {
                bestIndex = j;
            }
        }
        //swap into position i if necessary
        if (bestIndex != i) {
            Course tmp = courses[i];
            courses[i] = courses[bestIndex];
            courses[bestIndex] = tmp;
        }
    }
}