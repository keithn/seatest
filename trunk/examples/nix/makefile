CC = gcc
FILES = in_one.c in_two.c
OUT_EXE = out_executable

build: $(FILES)
        $(CC) -o $(OUT_EXE) $(FILES)

clean:
        rm -f *.o core

rebuild: clean build