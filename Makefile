# define the compiler to use
CC = g++

# define any compile-time flags
CFLAGS = -I${CURDIR} 
CFLAGS += -I/Library/Frameworks/SDL2.framework/Headers -F/Library/Frameworks -framework SDL2 -rpath /Library/Frameworks
CFLAGS += -I/Library/Frameworks/SDL2_image.framework/Headers -framework SDL2_image
CFLAGS += -I/Library/Frameworks/SDL2_mixer.framework/Headers -framework SDL2_mixer
CFLAGS += -std=c++17

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
