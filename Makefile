# Electible Makefile
# SE 2XC3 Lab 7.2 - Team Assignment
# Team 33
# Date: 2025-12-03

CC = gcc
CFLAGS = -std=c11 -Wall -Wextra -Iinclude
LIBS = -lm

# Source files
SOURCES = main.c data.c filter.c sort.c sort_code.c sort_difficulty.c sort_rating.c sort_title.c sort_workload.c sort_multi.c ui.c

# Build the program
all:
	$(CC) $(CFLAGS) -o main $(SOURCES) $(LIBS)

# Run the program
run: all
	./main

# Run with test input
test:
	chmod +x test.sh
	./test.sh > test_result.txt


# Clean up compiled files
clean:
	rm -f main test
	rm -f *.gcda *.gcno *.gcov main-*.gcda main-*.gcno test-*.gcda test-*.gcno

# Rebuild everything
rebuild: clean all

# Build with coverage flags
coverage: CFLAGS += -fprofile-arcs -ftest-coverage
coverage: LIBS += -lgcov
coverage: clean
	$(CC) $(CFLAGS) -o main $(SOURCES) $(LIBS)
	chmod +x test.sh
	./test.sh || true
	./main < /dev/null || true
	gcov *.c || true
	@echo ""
	@echo "Coverage files generated. Check *.gcov files for details."
	@echo "Use 'make clean' to remove coverage files."
