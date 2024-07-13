# define the compiler to use
CC = g++

# define any compile-time flags
CFLAGS = -I${CURDIR} -I/Library/Frameworks/SDL2.framework/Headers -F/Library/Frameworks -framework SDL2 -rpath /Library/Frameworks

# target file
TARGET = main.out

# Find all source files
#   Exclude:
# 		Testing files named ".*._test.cc"
# 		Examples folder
SRC = $(shell find . -name "*.cc" | grep -v "*_test.cc" | grep -v "examples\/")

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
