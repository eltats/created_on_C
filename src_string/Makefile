SRCS = s21_string_ekala.c\
	s21_string_gconn.c\
	s21_string_caquaman.c\
	s21_string_mabobbi.c\
	s21_string_sperses.c\
	s21_string_bonus.c\
	s21_string_special.c
	
OBJS = ${SRCS:.c=.o}
CC = gcc
CFLAGS = -Wall -Werror -Wextra


all: clean s21_string.a test

s21_string.a:
	${CC} -c ${SRCS}
	@ar rcs s21_string.a ${OBJS}
	@ranlib s21_string.a

test: s21_string.a unit_test

unit_test:
	${CC} -c s21_string-test.c
	${CC} s21_string-test.o s21_string.a -lcheck -o test 
	./test

gcov_report: s21_string.a
	@gcc --coverage s21_string-test.c -lcheck ${SRCS} -o unit-test
	@./unit-test
	@lcov -t "test" -o test.info -c -d .
	@genhtml -o report test.info
	
clean:
	@/bin/rm -rf *.o *.a test unit-test *.gcno *gcda report *.info


checks: cppcheck leaks style

style:
	python3 ../materials/linters/cpplint.py --extensions=c *.c *.h

cppcheck:
	cppcheck --enable=all --suppress=missingIncludeSystem . *.c

leaks: s21_string-test.c
	CK_FORK=no leaks --atExit -- ./test
	
main: s21_string.a main.c
	${CC} ${CFLAGS} main.c s21_string.a -o main

run: main
	./main
