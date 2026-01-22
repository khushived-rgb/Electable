/*
 * sort_multi.c
 * provides a stub implementation for multi-criteria sorting
 * Author: Anshika Patel
 * Date: 2025-12-03
 * version: v2.0.0
*/

#include <stddef.h>
#include "../include/sort.h"

/*
 * sort_mutli_criteria
 * sorts courses using a list of criteria
 * Parameters:
 *      - courses: array of Courses
 *      - count: number of elements in courses
 *      - criteria: array of SortCriteria description
 *      - num_criteria: number of criteria passed
*/
void sort_multi_criteria(Course* courses, int count, SortCriteria* criteria, int num_criteria) {
    if (courses == NULL || count <= 1 || criteria == NULL || num_criteria <= 0) {
        return;
    }

    int ascending = (criteria[0].order == ASCENDING) ? 1 : 0;

    //dispatch to the appropriate single field sort based on the first criterion
    switch (criteria[0].field) {
        case SORT_BY_DIFFICULTY:
            sort_by_difficulty(courses, count, ascending);
            break;
        case SORT_BY_WORKLOAD:
            sort_by_workload(courses, count, ascending);
            break;
        case SORT_BY_RATING:
            sort_by_rating(courses, count, ascending);
            break;
        case SORT_BY_COURSE_CODE:
            sort_by_course_code(courses, count, ascending);
            break;
        case SORT_BY_TITLE:
            sort_by_title(courses, count, ascending);
            break;
    }
}
