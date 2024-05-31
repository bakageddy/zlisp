CFLAGS=-g -Wall -Werror -Wextra -pedantic
TEST_FILES=$(wildcard(tests/*.c))
TESTS=$(patsubst %.c,%.o,$(TEST_FILES))

tests:$(TESTS)
	sh ./tests/run_tests.sh

%.o: %.c
	$CC) $^ -o $
