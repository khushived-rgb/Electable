//
// SE 2XC3 Lab 7.2: Electible
// main.c
// Team 33
// Date: 2025-12-03
// v2.0.0

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "include/data.h"
#include "include/ui.h"

#define DEFAULT_DATA_FILE "data/courses.csv"

// print help info
void display_usage(const char* program_name) {
    printf("Electible - McMaster First-Year Elective Finder\n");
    printf("SE 2XC3 Lab 7.2 Team Assignment\n\n");
    printf("Usage:\n");
    printf("%s [OPTIONS] [data_file]\n\n", program_name);
    printf("Usage Explanation:\n");
    printf("Running this program launches the Electible interactive menu system.\n");
    printf("Once started, you can browse courses, apply filters, sort results,add new courses, or view recommendations.\n\n");
    printf("Arguments:\n");
    printf("  data_file\n");
    printf("      The CSV must follow Electible's expected format:\n");
    printf("        - One course per line\n");
    printf("        - Fields separated by commas\n");
    printf("        - Columns (in order):\n");
    printf("            Title, Course Code, Subject, Difficulty, Workload,\n");
    printf("            Has Exam, Has Midterm, Rating, Description, Year Offered\n");
    printf("\n");


    printf("Options:\n");
    printf("  --help       Show this help message\n\n");
    printf("Description:\n");
    printf("This app will help Mcmaster first year eng students to find and explore elective based on their preferences.\n\n");
    printf("1.Browse All Courses: View complete list of available elctives.\n");
    printf("2.Filter Courses: Narrow down courses by subject, difficulty, workload, etc.\n");
    printf("3.Sort Courses: Organize courses by a selected field and order.\n");
    printf("4.Add New Courses: Add and rate courses to the exiting course. \n");
    printf("5. Recommendations: Top 10 recommended courses based on high ratings and moderate difficultly.\n");
    print_separator();
    printf("Examples:\n");
    printf("  %s\n", program_name);
    printf("       Run using the default data file.\n\n");
    printf("  %s data/my_courses.csv\n", program_name);
    printf("       Run using a custom course CSV file.\n\n");
    printf("  %s --help\n", program_name);
    printf("       Display this help message.\n\n");
}

int main(int argc, char* argv[]) {
    const char* data_file = DEFAULT_DATA_FILE;

    // check if user typed --help
    if (argc > 1) {
        if (strcmp(argv[1], "--help") == 0 || strcmp(argv[1], "-h") == 0) {
            display_usage(argv[0]);
            return 0;
        }
        data_file = argv[1];
    }

    // load courses from the CSV file
    printf("Loading courses from %s...\n", data_file);
    int count = 0;
    Course* courses = load_courses(data_file, &count);

    if (courses == NULL || count == 0) {
        fprintf(stderr, "Error: Failed to load courses from %s\n", data_file);
        fprintf(stderr, "Make sure the file exists and is formatted correctly.\n");
        fprintf(stderr, "Run '%s --help' for more info.\n", argv[0]);
        return 1;
    }

    printf("Successfully loaded %d courses.\n\n", count);

    // start the main menu
    handle_user_interaction(&courses, &count, data_file);

    // free up memory
    free_courses(courses);

    return 0;
}
