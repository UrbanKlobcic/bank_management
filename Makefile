# Makefile

# Compiler
CC = gcc

# Compiler flags
CFLAGS = -Wall

# Source files
SOURCES = banking.c data_management.c main.c communication.c

# Object files
OBJECTS = $(SOURCES:.c=.o)

# Executable name
EXECUTABLE = program.exe

# Targets
all: $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	$(CC) $(CFLAGS) $(OBJECTS) -o $(EXECUTABLE)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	del $(OBJECTS) $(EXECUTABLE)