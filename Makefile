# define the compiler to use
CC = clang

# define any compile-time flags
CFLAGS = -I/Library/Frameworks/SDL2.framework/Headers -F/Library/Frameworks -framework SDL2 -rpath /Library/Frameworks

# target file
TARGET = main

# source files
SRC = main.cpp

all: format $(TARGET)

# compile the target
$(TARGET): $(SRC)
	$(CC) $(SRC) $(CFLAGS) -o $(TARGET)


run: $(TARGET)
	./$(TARGET)

format:
	clang-format -i $(SRC)

clean:
	rm -f $(TARGET)
