
/*
 * ui.c
 * Handles all user interaction of Electible.
 * Shows menus, gets input, displays course info, and calls filtering/sorting functions from other modules
 * This is the “front end” of the app
 * Class: SFWRENG 2XC3
 * Developer: Yasmine Abdelmalek
 * Date: 2025/12/03
 * Version: v2.0.0
*/


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "../include/ui.h"
#include "../include/filter.h"
#include "../include/sort.h"
#include "../include/data.h"


//ANSI color codes for terminal output (found off google)
//these make the text displays colourful
#define COLOR_RESET   "\033[0m"
#define COLOR_BOLD    "\033[1m"
#define COLOR_CYAN    "\033[36m"
#define COLOR_GREEN   "\033[32m"
#define COLOR_YELLOW  "\033[33m"
#define COLOR_BLUE    "\033[34m"

/*disable colors on windows by default(if the colours dont work I'll uncomment)*/
/*#define COLOR_RESET ""
#define COLOR_BOLD ""
#define COLOR_CYAN ""
#define COLOR_GREEN ""
#define COLOR_YELLOW ""
#define COLOR_BLUE ""*/

/*Clear input buffer
*flushes any leftover characters from stdin until hit a newline of EOF
*leftover \n can cause issues later so this is just clean up
*/
void clear_input_buffer(void){
    int c;
    while ((c=getchar()) !='\n' && c != EOF);
}

//seperator line (seperates sections in UI)
void print_separator(void){
    printf("-----------------------------------------------------------------------------------------------------------------------------------------------------------------------\n");
}

/*pause and wait for user
*use after displaying smth important so user has time to read
*/
void pause_for_user(void){
    printf("\nPress ENTER to continue...");
    getchar();
}

/*get_in_inpit
*get integer input WITHIN RANGE
*Parameters: prompy,min,max
*Returns:valid int the user entered
*/
int get_int_input(const char* prompt,int min,int max){
    int value;
    int valid=0;

     while (!valid){
        printf("%s",prompt);
        int result=scanf("%d",&value);
        if (result==1){
            //successfully read num
            clear_input_buffer();
            if (value >=min && value<=max){
                valid =1;
            }else{
                printf("Input is invalid. Please enter a value between %d and %d.\n",min,max);
            }
        }else{
            //scanf failed to read num
            if (feof(stdin)){
                printf("\nNo more input available (EOF). Exiting.\n");
                exit(1);
            }
            clear_input_buffer();
            printf("Input is invalid. Please enter a number.\n");
        }

    }
    return value;
}

/*get_float_input
*asks user for float input within the range
*paramaters: prompt, min max
*keeps reprompting until user gives valid float
*handles inouts that arent numbers
*returns valid float that user inputed
*/
float get_float_input (const char* prompt,float min,float max){
    float value;
    int valid =0;

    while (!valid){
        printf("%s", prompt);
        if (scanf("%f", &value)==1){
            clear_input_buffer();
            if (value>=min && value<=max){
                valid=1;
            } else{
                printf("Input is invalid. Please enter a value between %.1f and %.1f.\n", min, max);
            }
        } else{
            clear_input_buffer();
            printf("Input is invalid. Please enter a number.\n");
        }
    }
    return value;
}

/*get_string_input
*gets basic string input from user
*pramaters: prompt(text to print),buffer (where to store string),max_length
*uses fgets to read characters
*strips trailing newline
*if gets to EOF buffer is left alone
*/
void get_string_input(const char* prompt,char* buffer,int max_length){
    printf("%s",prompt);
    if (fgets(buffer,max_length,stdin) != NULL){
        //removing newline
        buffer[strcspn(buffer,"\n")]='\0';
    }
}

/*display_menu
*prints  main menu
*shows options browse,filter,sort,add,recommendations,help,exit
*/
void display_menu(void){
    print_separator();
    printf("%s%s--- ELECTIBLE: McMaster's First-Year Elective Finder ---%s\n", COLOR_BOLD, COLOR_CYAN, COLOR_RESET);
    print_separator();
    printf("\n");
    printf("%s1.%s Browse All Courses\n", COLOR_GREEN, COLOR_RESET);
    printf("%s2.%s Filter Courses\n", COLOR_GREEN, COLOR_RESET);
    printf("%s3.%s Sort Courses\n",COLOR_GREEN, COLOR_RESET);
    printf("%s4.%s Add New Course\n",COLOR_GREEN, COLOR_RESET);
    printf("%s5.%s View Recommendations\n", COLOR_GREEN, COLOR_RESET);
    printf("%s6.%s Help\n",COLOR_GREEN, COLOR_RESET);
    printf("%s7.%s Exit\n", COLOR_GREEN, COLOR_RESET);
    printf("\n");
}

/*display_course_row
*helper func that displays a course in tablen row format
*parameters: course,index
*static because only used in this file
*/
static void display_course_row(Course course, int index){
    printf("%-3d %-14s %-80s %d/5       %d/5       %-8s %-10s %.1f/5\n",
       index + 1,
       course.course_code,
       course.title,
       course.difficulty,
       course.workload,
       course.has_exam ? "Yes" : "No",
       course.has_midterm ? "Yes" : "No",
       course.rating);
}

/*display_courses
*prints list of courses in table
*param: courses (pointer to an array), count (number of courses in array)
*/
void display_courses(Course* courses,int count){
    if (courses==NULL ||count<= 0){
        printf("\n%sNo courses to display.%s\n",COLOR_YELLOW,COLOR_RESET);
        return;
    }
    printf("\n%s%sFound %d courses:%s\n\n",COLOR_BOLD,COLOR_BLUE,count,COLOR_RESET);
    //Table  header
    printf("%-3s %-14s %-80s %-10s %-10s %-8s %-10s %-8s\n",
       "#", "Code", "Title", "Diff", "Work","Exam","Midterm", "Rating");
       print_separator();

    //display each course
    for (int i=0; i<count;i++){
        display_course_row(courses[i], i);
    }

    printf("\n");
}


/*display_course_detail
*shows all displays for a single course
param: course: course whos details we wanna show
*prints title,code,difficulty,workload,exam/midterm, rating,description
*/
void display_course_detail(Course course){
    print_separator();
    printf("%s%s%s%s\n",COLOR_BOLD,COLOR_CYAN,course.title,COLOR_RESET);
    printf("Course Code:     %s\n", course.course_code);
    printf("Difficulty:      %d/5\n",course.difficulty);
    printf("Workload:        %d/5\n", course.workload);
    printf("Has Exam:        %s\n",course.has_exam ? "Yes" : "No");
    printf("Has Midterm:     %s\n",course.has_midterm ? "Yes" : "No");
    printf("Rating:          %.1f/5\n", course.rating);
    printf("\nDescription:\n%s\n",course.description);
    print_separator();
}

/*get_filter_preferences
*asks user for filter preferences
*builds and returns FilterCriteria struct which reflects user's filter choices
*user can skip fields by pressing enter or using invalid range (filters will be disabled)
*returns FilterCriteria struct
*/
FilterCriteria get_filter_preferences(void){
    FilterCriteria criteria=create_default_filter_criteria();

    printf("\n%s%s------Filter Courses------%s\n", COLOR_BOLD,COLOR_CYAN,COLOR_RESET);
    printf("Leave filters blank or enter -1 to skip.\n\n");

    //dificulty
    printf("\nFilter by difficulty?(1-5)\n");
    char response[10];
    //min difficulty
    get_string_input("Minimum difficulty (ENTER to skip): ",response,sizeof(response));
    if (strlen(response)>0){
        criteria.min_difficulty=atoi(response);
        if (criteria.min_difficulty<1 ||criteria.min_difficulty>5){
            criteria.min_difficulty=-1;
        }
    }
    //max difficulty
    get_string_input("Maximum difficulty (ENTER to skip): ",response,sizeof(response));
    if (strlen(response)>0){
        criteria.max_difficulty=atoi(response);
        if (criteria.max_difficulty<1||criteria.max_difficulty>5){
            criteria.max_difficulty=-1;
        }
    }

    //workload filter
    printf("\nFilter by workload?(1-5)\n");
    get_string_input("Minimum workload (ENTER to skip): ",response, sizeof(response));
    if (strlen(response)>0){
        criteria.min_workload=atoi(response);
        if (criteria.min_workload<1 ||criteria.min_workload>5) {
            criteria.min_workload=-1;
        }
    }
    get_string_input("Maximum workload (ENTER to skip): ",response,sizeof(response));
    if (strlen(response)>0){
        criteria.max_workload=atoi(response);
        if (criteria.max_workload<1 ||criteria.max_workload >5){
            criteria.max_workload=-1;
        }
    }

//exam filter
printf("\nFilter by exam presence?\n");
printf("1. Courses with exams\n");
printf("2. Courses without exams\n");
printf("3. No preference\n");
int exam_choice =get_int_input("Choice: ",1,3);
if (exam_choice ==1){
    criteria.has_exam=1;
} else if (exam_choice==2){
    criteria.has_exam=0;
}

//midterm filter
printf("\nFilter by midterm presence?\n");
printf("1. Courses with midterms\n");
printf("2. Courses without midterms\n");
printf("3. No preference\n");
int midterm_choice=get_int_input("Choice: ",1,3);
if (midterm_choice ==1){
    criteria.has_midterm=1;
}else if (midterm_choice==2){
    criteria.has_midterm=0;
}

//ratinf filter
printf("\nFilter by minimum rating? (0.0-5.0)\n");
    get_string_input("Minimum rating (ENTER to skip):", response, sizeof(response));
    if (strlen(response) >0){
        criteria.min_rating = (float)atof(response);
        if (criteria.min_rating <0.0f || criteria.min_rating > 5.0f) {
            criteria.min_rating =-1.0f;
        }
    }
    return criteria;
}

/*get_sort_preferences
*get sort preferences from user
*parameters:
*       criteria:if success will point to array of SortCriteria
        num_criteria: how many criteria are stored
*lets user pick filed
*lets user pick ascending or descending
*allocated memory for *criteria
*if that fails, *num_criteria is set to 0 and *criteria stays NULL
*/
void get_sort_preferences(SortCriteria** criteria, int* num_criteria) {
    printf("\n%s%s---Sort Courses---%s\n",COLOR_BOLD,COLOR_CYAN, COLOR_RESET);
    printf("Select sort field:\n");
    printf("1.Difficulty\n");
    printf("2.Workload\n");
    printf("3.Rating\n");
    printf("4.Course Code\n");
    printf("5.Title\n");

    int field_choice=get_int_input("Sort by: ",1,5);

    printf("\nSort order:\n");
    printf("1.Ascending\n");
    printf("2.Descending\n");
    int order_choice=get_int_input("Order: ", 1,2);

    *criteria =(SortCriteria*)malloc(sizeof(SortCriteria));
    if (*criteria==NULL){
        *num_criteria=0;
        return;
    }

    //map field choice starting from 0
    (*criteria)[0].field=(SortField)(field_choice-1);
    (*criteria)[0].order=(order_choice ==1) ? ASCENDING:DESCENDING;
    *num_criteria=1;
}

/*get_new_course_input
*get new course input from user
*field collected: title,course code,difficulty,workload,has exam/mid, rating, desciprtion, year offered
*returns fully filled course struct
*/
Course get_new_course_input(void){
    Course course;
    printf("\n%s%s=== Add New Course ===%s\n",COLOR_BOLD,COLOR_CYAN,COLOR_RESET);
    get_string_input("Course title: ",course.title,sizeof(course.title));
    get_string_input("Course code (e.g., SFWRENG 2XC3): ",course.course_code,sizeof(course.course_code));

    course.difficulty = get_int_input("Difficulty (1-5): ",1,5);
    course.workload = get_int_input("Workload (1-5): ",1,5);

    printf("Has exam? (1=Yes, 0=No): ");
    course.has_exam = get_int_input("", 0, 1);
    printf("Has midterm? (1=Yes, 0=No): ");
    course.has_midterm = get_int_input("", 0, 1);
    course.rating = get_float_input("Rating (0.0-5.0): ", 0.0f, 5.0f);
    get_string_input("Description: ", course.description, sizeof(course.description));
    course.year_offered = get_int_input("Year offered (e.g., 2025): ", 2020, 2030);
    return course;
}

/*display_help
*prints help info
*gives short overview of the app and everything in main menu
*just printed text
*/
void display_help(void){
    print_separator();
    printf("%s%s----HELP----%s\n\n",COLOR_BOLD,COLOR_CYAN,COLOR_RESET);
    printf("%sWelcome to Electible!%s\n\n",COLOR_BOLD,COLOR_RESET);
    printf("This app will help Mcmaster first year eng students to find and explore elective based on their preferences.\n\n");
    printf("1.Browse All Courses: View complete list of available elctives.\n");
    printf("2.Filter Courses: Narrow down courses by subject, difficulty, workload, etc.\n");
    printf("3.Sort Courses: Organize courses by a selected field and order.\n");
    printf("4.Add New Courses: Add and rate courses to the exiting course. \n");
    printf("5. Recommendations: Top 10 recommended courses based on high ratings and moderate difficultly.\n");
    print_separator();
}

/*display_recommendations
*shows list of  recommended courses based on high ratings and moderate difficulty
*paramters:
        courses:pointer to full list of courses
        count: number of courses in that list
*builds FilterCriteria
*uses apply_multiple_filters() to get matching courses
*sorts them (descending)
*displays up to top 10
*frees the temp arrawy created by apply_multiple_filters
*/
void display_recommendations(Course* courses,int count) {
    printf("\n%s%s----Recommended Courses----%s\n", COLOR_BOLD, COLOR_CYAN, COLOR_RESET);
    printf("Based on high ratings and moderate difficulty.\n\n");

    //Filter for highly rated courses with moderate difficulty (1-3)
    FilterCriteria criteria=create_default_filter_criteria();
    criteria.min_rating= 4.0f;
    criteria.min_difficulty=1;
    criteria.max_difficulty=3;

    int rec_count;
    Course* recommendations=apply_multiple_filters(courses, count,criteria, &rec_count);

    if (recommendations != NULL && rec_count>0) {
        //descending rating
        sort_by_rating(recommendations, rec_count,0);

        //top 10 or less
        int display_count = (rec_count<10) ? rec_count:10;
        display_courses(recommendations,display_count);

        free(recommendations);
    } else {
        printf("No recommendations found\n");
    }
}


/*handle_user_interaction
*main UI loop
*paramters:
        courses: pointer to the pointer of the main Course array
        count: point to number of courses
        filename: name if the data file where courses are stored
*shows main menu
*asks user for chouce (1-7)
*runs actions
*/
void handle_user_interaction(Course** courses, int* count, const char* filename) {
    (void)filename;// toavoid unused parameter warning

    int running =1;
    //working_set is what we currently display and sort and filter
    Course* working_set=*courses;
    int working_count= *count;
    int is_filtered =0;//0=OG array

    while (running){
        display_menu();

        int choice=get_int_input("Enter choice (1-7): ",1,7);

        switch (choice){
            case MENU_BROWSE:{
                //reset full datat set
                if (is_filtered && working_set != *courses){
                    free(working_set);
                }
                working_set= *courses;
                working_count= *count;
                is_filtered = 0;

                display_courses(working_set, working_count);
                pause_for_user();
                break;
            }

            case MENU_FILTER:{
                FilterCriteria criteria =get_filter_preferences();
                if (is_filtered && working_set != *courses){
                    free(working_set);
                }
                int filtered_count=0;
                Course* filtered = apply_multiple_filters(*courses,*count,criteria,&filtered_count);

                if (filtered != NULL && filtered_count>0){
                    working_set=filtered;
                    working_count=filtered_count;
                    is_filtered =1;

                    printf("\n%sFiltering complete%s\n", COLOR_GREEN, COLOR_RESET);
                    display_courses(working_set, working_count);
                }else{
                    printf("\n%sNo courses match your filters%s\n", COLOR_YELLOW, COLOR_RESET);
                    working_set=*courses;
                    working_count=*count;
                    is_filtered=0;
                }

                pause_for_user();
                break;
            }

            case MENU_SORT:{
                SortCriteria* sort_criteria=NULL;
                int num_criteria=0;
                get_sort_preferences(&sort_criteria,&num_criteria);

                if (sort_criteria != NULL && num_criteria>0) {
                    sort_multi_criteria(working_set,working_count,sort_criteria,num_criteria);
                    printf("\n%sSorting complete!%s\n",COLOR_GREEN,COLOR_RESET);
                    display_courses(working_set,working_count);
                    free(sort_criteria);
                } else {
                    printf("\n%sSorting failed%s\n", COLOR_YELLOW, COLOR_RESET);
                }

                pause_for_user();
                break;
            }

            case MENU_ADD:{
                Course new_course=get_new_course_input();
                int result = add_course(courses,count,new_course);

                if (result == DATA_SUCCESS){
                    printf("\n%sCourse added successfully!%s\n", COLOR_GREEN, COLOR_RESET);

                    //save to file
                    if (save_courses(*courses, *count, filename) == DATA_SUCCESS) {
                        printf("%sChanges saved to %s.%s\n", COLOR_GREEN, filename,COLOR_RESET);
                    } else {
                        printf("%sWarning:Could not save to file%s\n",COLOR_YELLOW,COLOR_RESET);
                    }

                    //Reset working set
                    if (!is_filtered) {
                        working_set = *courses;
                        working_count = *count;
                    }
                } else{
                    printf("\n%sError adding course: %s%s\n",COLOR_YELLOW,
                           get_data_error_message(result),COLOR_RESET);
                }

                pause_for_user();
                break;
            }

            case MENU_RECOMMENDATIONS:{
                display_recommendations(*courses, *count);
                pause_for_user();
                break;
            }

            case MENU_HELP:{
                display_help();
                pause_for_user();
                break;
            }

            case MENU_EXIT:{
                printf("\nThank you for using Electible!\n");
                running = 0;

                //clean up filtered working_set only if neededd
                if (is_filtered && working_set != *courses){
                    free(working_set);
                }
                break;
            }
        }
    }
}
