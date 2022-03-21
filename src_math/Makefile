COMPILER = gcc
#CFLAGS = -Wall -Wextra -Werror
CFLAGS = -Wall -std=c11

# C_LIBS
ifeq ($(OS),Windows_NT) # MinGW
	C_LIBS = -lcheck -lm -lpthread -ls21_math -L.
else
	UNAME_S := $(shell uname -s)
	ifeq ($(UNAME_S),Linux) # Linux
		C_LIBS = -lcheck -lsubunit -lm -lpthread -lrt -ls21_math -L.
	endif
	ifeq ($(UNAME_S),Darwin) # Apple
 		C_LIBS = -lcheck -ls21_math -L. 
#		C_LIBS = pkg-config --cflags --libs check
#		C_LIBS = -I ~/.brew/include -lcheck -pthread -L ~/.brew/Cellar/check/0.15.2/lib
	endif
endif

TEST_SW = -DTEST_NAME_

all rebuild: clean s21_math.a s21_math_test.o

clean:
	rm -rf s21_*.o *.a s21_*.exe s21_tests *.gcno *.gcda *.gcov s21_math_coverage.info coverage_report

s21_math.o: clean s21_math.c
	$(COMPILER) $(CFLAGS) -c s21_math.c

s21_math.a: s21_math.o
	ar rc libs21_math.a s21_math.o
	ranlib libs21_math.a
	cp libs21_math.a s21_math.a

s21_math_test.o: s21_math_test.c
	$(COMPILER) $(CFLAGS) -c s21_math_test.c

# tests
test: clean all 
	$(COMPILER) $(CFLAGS) -c s21_math_test.c $(TEST_SW)all
	$(COMPILER) $(CFLAGS) s21_math.a s21_math_test.o $(C_LIBS) -o s21_tests
	./s21_tests

test_abs: clean s21_math.a
	$(COMPILER) $(CFLAGS) -c s21_math_test.c $(TEST_SW)abs
	$(COMPILER) $(CFLAGS) s21_math.a s21_math_test.o $(C_LIBS) -o s21_tests
	./s21_tests

test_acos: clean s21_math.a
	$(COMPILER) $(CFLAGS) -c s21_math_test.c $(TEST_SW)acos
	$(COMPILER) $(CFLAGS) s21_math.a s21_math_test.o $(C_LIBS) -o s21_tests
	./s21_tests

test_asin: clean s21_math.a
	$(COMPILER) $(CFLAGS) -c s21_math_test.c $(TEST_SW)asin
	$(COMPILER) $(CFLAGS) s21_math.a s21_math_test.o $(C_LIBS) -o s21_tests
	./s21_tests

test_atan: clean s21_math.a
	$(COMPILER) $(CFLAGS) -c s21_math_test.c $(TEST_SW)atan
	$(COMPILER) $(CFLAGS) s21_math.a s21_math_test.o $(C_LIBS) -o s21_tests
	./s21_tests

test_ceil: clean s21_math.a
	$(COMPILER) $(CFLAGS) -c s21_math_test.c $(TEST_SW)ceil
	$(COMPILER) $(CFLAGS) s21_math.a s21_math_test.o $(C_LIBS) -o s21_tests
	./s21_tests

test_cos: clean s21_math.a
	$(COMPILER) $(CFLAGS) -c s21_math_test.c $(TEST_SW)cos
	$(COMPILER) $(CFLAGS) s21_math.a s21_math_test.o $(C_LIBS) -o s21_tests
	./s21_tests

test_exp: clean s21_math.a
	$(COMPILER) $(CFLAGS) -c s21_math_test.c $(TEST_SW)exp
	$(COMPILER) $(CFLAGS) s21_math.a s21_math_test.o $(C_LIBS) -o s21_tests
	./s21_tests

test_fabs: clean s21_math.a
	$(COMPILER) $(CFLAGS) -c s21_math_test.c $(TEST_SW)fabs
	$(COMPILER) $(CFLAGS) s21_math.a s21_math_test.o $(C_LIBS) -o s21_tests
	./s21_tests

test_floor: clean s21_math.a
	$(COMPILER) $(CFLAGS) -c s21_math_test.c $(TEST_SW)floor
	$(COMPILER) $(CFLAGS) s21_math.a s21_math_test.o $(C_LIBS) -o s21_tests
	./s21_tests

test_fmod: clean s21_math.a
	$(COMPILER) $(CFLAGS) -c s21_math_test.c $(TEST_SW)fmod
	$(COMPILER) $(CFLAGS) s21_math.a s21_math_test.o $(C_LIBS) -o s21_tests
	./s21_tests

test_log: clean s21_math.a
	$(COMPILER) $(CFLAGS) -c s21_math_test.c $(TEST_SW)log
	$(COMPILER) $(CFLAGS) s21_math.a s21_math_test.o $(C_LIBS) -o s21_tests
	./s21_tests

test_pow: clean s21_math.a
	$(COMPILER) $(CFLAGS) -c s21_math_test.c $(TEST_SW)pow
	$(COMPILER) $(CFLAGS) s21_math.a s21_math_test.o $(C_LIBS) -o s21_tests
	./s21_tests

test_sin: clean s21_math.a
	$(COMPILER) $(CFLAGS) -c s21_math_test.c $(TEST_SW)sin
	$(COMPILER) $(CFLAGS) s21_math.a s21_math_test.o $(C_LIBS) -o s21_tests
	./s21_tests

test_sqrt: clean s21_math.a
	$(COMPILER) $(CFLAGS) -c s21_math_test.c $(TEST_SW)sqrt
	$(COMPILER) $(CFLAGS) s21_math.a s21_math_test.o $(C_LIBS) -o s21_tests
	./s21_tests

test_tan: clean s21_math.a
	$(COMPILER) $(CFLAGS) -c s21_math_test.c $(TEST_SW)tan
	$(COMPILER) $(CFLAGS) s21_math.a s21_math_test.o $(C_LIBS) -o s21_tests
	./s21_tests
    
    
# checks
check:
	python3 ../materials/linters/cpplint.py --extensions=c *.c *.h ./test/*.c

leakscheck_linux: clean
	$(COMPILER) $(CFLAGS) -g -O0 -c s21_math.c
	$(COMPILER) $(CFLAGS) -g -O0 -c s21_math_test.c $(TEST_SW)all
	ar rc libs21_math.a s21_math.o
	ranlib libs21_math.a
	cp libs21_math.a s21_math.a
	$(COMPILER) $(CFLAGS) -g -O0 s21_math.a s21_math_test.o $(C_LIBS) -o s21_tests
	valgrind --log-fd=9 --leak-check=yes ./s21_tests 9>&1 | (! grep -A5 "are definitely lost")

leakscheck_mac: clean
	$(COMPILER) $(CFLAGS) -g -O0 -c s21_math.c
	$(COMPILER) $(CFLAGS) -g -O0 -c s21_mathg_test.c $(TEST_SW)all
	ar rc libs21_math.a s21_math.o
	ranlib libs21_math.a
	cp libs21_math.a s21_math.a
	$(COMPILER) $(CFLAGS) -g -O0 s21_math.a s21_math_test.o $(C_LIBS) -o s21_tests
	CK_FORK=no leaks --atExit -- ./s21_tests

#gcov_report
gcov_report1: # uses gcov, but doesn't generate an html report
	$(COMPILER) $(CFLAGS) --coverage -c s21_math.c
	$(COMPILER) $(CFLAGS) -c s21_math_test.c $(TEST_SW)all
	$(COMPILER) $(CFLAGS) --coverage s21_math.o s21_math_test.o $(C_LIBS) -o s21_tests
	./s21_tests
	gcov s21_math.c

gcov_report: clean # does not use gcov, but generates an html report indeed
	$(COMPILER) $(CFLAGS) --coverage -c s21_math.c
	$(COMPILER) $(CFLAGS) -c s21_math_test.c $(TEST_SW)all
	ar rc libs21_math.a s21_math.o
	ranlib libs21_math.a
	cp libs21_math.a s21_math.a
	$(COMPILER) $(CFLAGS) --coverage s21_math.a s21_math_test.o $(C_LIBS) -o s21_tests
	./s21_tests
	lcov -c --directory . --output-file s21_math_coverage.info
	genhtml s21_math_coverage.info --output-directory coverage_report

