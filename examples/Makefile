# define the compiler to use
CC = clang

# define any compile-time flags
CFLAGS = -I/Library/Frameworks/SDL2.framework/Headers -F/Library/Frameworks -framework SDL2 -rpath /Library/Frameworks

# compile the target
build:
	$(CC) detect_input.cc $(CFLAGS) -o detect_input.out

run_detect_input:
	./detect_input.out

format:
	clang-format -i detect_input.cc

clean:
	rm -f *.out
