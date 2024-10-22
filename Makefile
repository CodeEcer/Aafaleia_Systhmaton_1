# Compiler and flags
CC = gcc
CFLAGS = -g -Wall -IC:/msys64/mingw64/include
LDFLAGS = -LC:/msys64/mingw64/lib -lgmp -lgmpxx -lpsapi

# Executable and object files
EXEC = main.exe
OBJS = main.o prime_generation.o key_generation.o encrypt_rsa.o decrypt_rsa.o performance.o
TXT_FILE = test_performance.txt

# Rule for building the entire program
$(EXEC): $(OBJS) $(TXT_FILE)
	$(CC) $(OBJS) -o $(EXEC) $(LDFLAGS)

# Rule to create test_performance.txt with predefined content
$(TXT_FILE):
	echo "This is the initial content for test_performance.txt." > $(TXT_FILE)

# Compile source files into object files
main.o: main.c
	$(CC) $(CFLAGS) -c main.c -o main.o

prime_generation.o: prime_generation.c
	$(CC) $(CFLAGS) -c prime_generation.c -o prime_generation.o

key_generation.o: key_generation.c
	$(CC) $(CFLAGS) -c key_generation.c -o key_generation.o

encrypt_rsa.o: encrypt_rsa.c
	$(CC) $(CFLAGS) -c encrypt_rsa.c -o encrypt_rsa.o

decrypt_rsa.o: decrypt_rsa.c
	$(CC) $(CFLAGS) -c decrypt_rsa.c -o decrypt_rsa.o

performance.o: performance.c
	$(CC) $(CFLAGS) -c performance.c -o performance.o

# Clean rule to remove object files, executable, and text file
clean:
	rm -f $(OBJS) $(EXEC) $(TXT_FILE)

# Run the executable
run: $(EXEC)
	./$(EXEC)
