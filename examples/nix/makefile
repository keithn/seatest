CC = gcc
FILES = example_project.c test_suite_one.c test_suite_two.c ../../src/seatest.c
OUT_EXE = example

build: $(FILES)
	$(CC) -o $(OUT_EXE) $(FILES) -I ../../src

clean:
	rm -f *.o core

rebuild: clean build
