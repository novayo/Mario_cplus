ROOT := $(realpath ${CURDIR}/..)

# define the compiler to use
CC = g++

# define any compile-time flags
CFLAGS = -I${ROOT}
CFLAGS += -I/Library/Frameworks/SDL2.framework/Headers -F/Library/Frameworks -framework SDL2 -rpath /Library/Frameworks
CFLAGS += -I/Library/Frameworks/SDL2_mixer.framework/Headers -framework SDL2_mixer
CFLAGS += -std=c++17

# Find all source files
#   Exclude:
# 		Testing files named ".*._test.cc"
# 		Examples folder
# 		main.cc
SRCS = $(shell find ${ROOT} -name "*.cc" | grep -v "*_test.cc" | grep -v "examples\/" | grep -v "main.cc")

# Find all tests
TESTS := $(shell find . -name "*.cc" -exec basename -s '.cc' {} \;)

help:
	@echo "    <file_name>"
	@echo "        Compile and run a example file."
	@echo "        Example:"
	@echo "        	# detect_input.cc"
	@echo "        	make detect_input"
	@echo "    format"
	@echo "        Format all examples files."
	@echo "    clean"
	@echo "        Remove compiled files."

# Compile and run an example
$(TESTS):
	$(CC) $@.cc $(SRCS) $(CFLAGS) -o $@.out
	./$@.out

format:
	clang-format -i *.cc

clean:
	rm -f *.out
