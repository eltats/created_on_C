SRCS = s21_decimal.c
	
OBJS = ${SRCS:.c=.o}
CC = gcc
CFLAGS = -Wall -Werror -Wextra

all: clean s21_decimal.a test

s21_decimal.a: ${SRCS}
	${CC} ${CFLAGS} -c ${SRCS}
	@ar rcs s21_decimal.a ${OBJS}
	@ranlib s21_decimal.a

test: s21_decimal.a unit_test

unit_test:
	${CC} ${CFLAGS} -c s21_decimal-test.c
	${CC} s21_decimal-test.o s21_decimal.a -lcheck -o test
	./test

gcov_report: s21_decimal.a
	@gcc --coverage s21_decimal-test.c -lcheck ${SRCS} -o unit-test
	@./unit-test
	@lcov -t "test" -o test.info -c -d .
	@genhtml -o report test.info
	
clean:
	@/bin/rm -rf *.o *.a test unit-test *.gcno *gcda report *.info main

checks: cppcheck leaks style

style:
	python3 ../materials/linters/cpplint.py --extensions=c *.c *.h

cppcheck:
	cppcheck --enable=all --suppress=missingIncludeSystem . *.c

leaks: s21_decimal-test.c
	CK_FORK=no leaks --atExit -- ./test
	
main: s21_decimal.a main.c
	${CC} ${CFLAGS} main.c s21_decimal.a -o main

run: main
	./main