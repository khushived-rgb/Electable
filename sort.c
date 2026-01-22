/*
 * sort.c
 * Provides a simple interactive driver to demonstrate and test sorting on course arrays
 * prompts the user for a sort field and order, calls the corresponding sort function and print the sorted results
 * Author: Anshika Patel
 * Date: 2025-12-03
 * Version: v2.0.0
*/

#include <stdio.h>
#include "../include/filter.h"
#include "../include/sort.h"

/*
 * sort_main
 * Demonstrates sorting functioanlity using a small, hardcoded course array
 * Asks the user to choose the sort field and order, performs the sort, and prints the sorted list
 * No parameters
 * Returns:
 *      int (0 on success, 1 if an invalid sort choice)
*/
int sort_main(void) {
    //following is onyl for testing this code locally. When the actual code is ran, it extracts the courses form the courses.csv file
    Course courses[] = {
        { "Intro to Computing", "COMP-100", "COMP", 2, 3, 1, 1, 4.2f, "Basics", 2025 },
        { "Algorithms",         "COMP-200", "COMP", 4, 4, 1, 1, 4.8f, "Algo",   2025 },
        { "Databases",          "COMP-250", "COMP", 3, 3, 0, 1, 4.5f, "DB",     2025 },
        { "OS",                 "COMP-300", "COMP", 5, 5, 1, 1, 4.1f, "OS",     2025 }
    };
    int n = (int)(sizeof(courses)/sizeof(courses[0]));

    // print statement
    int choice, order;
    printf("Choose a sorting option:\n");
    printf("1. Difficulty\n");
    printf("2. Workload\n");
    printf("3. Rating\n");
    printf("4. Course Code\n");
    printf("5. Title\n");
    printf("Enter choice (1-5): ");
    scanf("%d", &choice);

    printf("Sort order? (1 = Ascending, 0 = Descending): ");
    scanf("%d", &order);

    //calling the functions based on the user input
    switch (choice){
    	case 1: sort_by_difficulty(courses, n, order);
		break;
	case 2: sort_by_workload(courses, n, order);
		break;
	case 3: sort_by_rating(courses, n, order);
		break;
        case 4: sort_by_course_code(courses, n, order);
		break;
        case 5: sort_by_title(courses, n, order);
		break;
        default: printf("Invalid choice!\n"); return 1;
    }

    printf("\nSorted courses:\n");
    for (int i = 0; i < n; ++i) {
        //printing the sorted list
        printf("%s (%s): diff=%d workload=%d rating=%.1f\n",
               courses[i].title, courses[i].course_code,
               courses[i].difficulty, courses[i].workload, courses[i].rating);
    }

    return 0;
}
