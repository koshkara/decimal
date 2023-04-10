FLAGS = -Wall -Werror -Wextra -std=c11
FUNC_C = s21_from_decimal_to_float.c s21_from_decimal_to_int.c s21_from_float_to_decimal.c s21_from_int_to_decimal.c
FUNC_O = s21_from_decimal_to_float.o s21_from_decimal_to_int.o s21_from_float_to_decimal.o s21_from_int_to_decimal.o

all: s21_decimal.a

rebuild: clean all

clean:
	rm -rf *.o out *.info *.gcda *.gcno *.gcov *.gch *.out *.a test

s21_decimal.a: s21_decimal.o
	ar rc s21_decimal.a $(FUNC_O)
	ranlib s21_decimal.a

s21_decimal.o:
	gcc $(FLAGS) -c $(FUNC_C)

test: clean
	gcc $(FLAGS) -fprofile-arcs -ftest-coverage $(FUNC_C) -o test  s21_test.c -lcheck -lm -lpthread
	./test

gcov_report: test
	gcov s21_test.c
	lcov --capture --directory . --output-file coverage.info
	genhtml coverage.info --output-directory out

style:
	clang-format -n *.c

cppcheck:
	cppcheck --enable=all --suppress=missingIncludeSystem ./
