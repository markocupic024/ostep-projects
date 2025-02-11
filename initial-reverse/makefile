# Define object files
OBJS = main.o dynamic_array.o

# Compiler flags
CFLAGS = -O -Wall

# Targets

# Main target to build the executable for the application
reverse: $(OBJS)
	gcc -o reverse $(OBJS)

# Compile main.c to main.o for the application
main.o: main.c
	gcc $(CFLAGS) -c main.c

# Compile dynamic_array.c to dynamic_array.o
dynamic_array.o: dynamic_array.c
	gcc $(CFLAGS) -c dynamic_array.c

# Target to build and run the dynamic array tests
test_dynamic_array: dynamic_array.o dynamic_array_test.o
	gcc $(CFLAGS) -o test_runner dynamic_array.o dynamic_array_test.o
	./test_runner

# Compile dynamic_array_test.c to dynamic_array_test.o (for the dynamic array test executable)
dynamic_array_test.o: dynamic_array_test.c
	gcc $(CFLAGS) -c dynamic_array_test.c

# Clean up object files and executables
clean:
	rm -f main.o dynamic_array.o reverse dynamic_array_test.o test_runner
