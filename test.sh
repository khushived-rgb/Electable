#!/bin/bash
# Electible Test Script
# Team 33

# Basic test script for the Electible program
# Tests the main features to make sure everything works

echo "Starting Electible tests..."
echo ""

# Check if program exists
if [ ! -f "./main" ]; then
    echo "ERROR: main executable not found"
    echo "Run 'make' or 'make all' first"
    exit 1
fi

# Check if data file exists
if [ ! -f "data/courses.csv" ]; then
    echo "ERROR: data/courses.csv not found"
    exit 1
fi

echo "Files found OK"
echo ""

passed=0
failed=0

# Helper function to run a test
test_feature() {
    name=$1
    input=$2
    search_for=$3

    echo "Testing: $name"

    result=$(echo -e "$input" | timeout 3 ./main 2>&1 || true)

    if echo "$result" | grep -qi "$search_for"; then
        echo "  [PASS]"
        passed=$((passed + 1))
    else
        echo "  [FAIL] - couldn't find: $search_for"
        failed=$((failed + 1))
    fi
}

echo "=== Basic Tests ==="
# Test 1: Program runs and exits
test_feature "Program exits cleanly" "7" "Thank you"

# Test 2: Main menu shows up
test_feature "Main menu displays" "7" "ELECTIBLE"

# Test 3: Can browse courses
test_feature "Browse all courses" "1\n7" "Found"

# Test 4: Help works
test_feature "Help menu" "6\n7" "Browse"

echo ""
echo "=== Filter Tests ==="
# Test 5: Filter by difficulty
test_feature "Filter by difficulty" "2\n2\n1\n3\n7\n7" "Diff"

echo ""
echo "=== Sort Tests ==="
# Test 6: Sort by code
test_feature "Sort by course code" "3\n1\n1\n7\n7" "Code"

# Test 7: Sort by title
test_feature "Sort by title" "3\n2\n1\n7\n7" "Title"

# Test 8: Sort by difficulty
test_feature "Sort by difficulty" "3\n3\n1\n7\n7" "Diff"

# Test 9: Sort by rating
test_feature "Sort by rating" "3\n5\n2\n7\n7" "Rating"

echo ""
echo "=== Other Features ==="
# Test 10: Add course (just test that it doesn't crash)
test_feature "Add course menu" "4\n\n7" "ELECTIBLE"

# Test 11: Recommendations
test_feature "View recommendations" "5\n7" "Recommend"

echo ""
echo "=== Error Handling ==="
# Test 12: Invalid input
test_feature "Invalid menu option" "99\n7" "invalid"

# Test 13: Handle letters
test_feature "Non-numeric input" "abc\n7" "invalid"

echo ""
echo "=== Advanced Tests ==="
# Test 14: Multiple operations
test_feature "Chain operations" "1\n3\n5\n1\n7\n7" "courses"

# Test 15: Course format check
test_feature "Course display format" "1\n7" "Code.*Title.*Diff"

echo ""
echo "================================"
echo "Test Results:"
echo "  Passed: $passed"
echo "  Failed: $failed"
total=$((passed + failed))
echo "  Total:  $total"

if [ $failed -eq 0 ]; then
    echo ""
    echo "All tests passed!"
    exit 0
else
    echo ""
    echo "Some tests failed"
    exit 1
fi
