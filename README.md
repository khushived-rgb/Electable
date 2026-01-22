Electible is a C-based console application designed to help McMaster first-year engineering students browse, sort, and filter elective courses based on their preferences. 

Features:
-Browse Courses: View all available electives 
-Sort Courses: Sort by difficulty, workload, rating, course code, or title
-Filter Courses: Filter by subject, difficulty range, workload, exam presence, and rating
-Add New Course: Add a course 
-Recommendations: Suggest courses based on user preferences 

Team Members: 
Khushi Ved
Anshika Patel
Yasmine Abdelmalek
Amanda Wu


How it Works:
-Data Model: Course struct stores course details (title, code, difficulty, workload, rating, etc.)

-Sorting: Each sort_*.c file implements selection sort for one field

-Multi-Criteria Sorting: sort_multi.c uses SortCriteria to sort by multiple fields (currently, it sorts by the first criterion)

-UI: displays menus, takes user input, and prints results
