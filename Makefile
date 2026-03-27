# Compiler
CC = gcc

# Flags
# CFLAGS = -Wall -Wextra -std=c11

# Output binary
TARGET = music_player

# Source files
SRCS = main.c song.c album.c playlist.c action.c lib.c

# Object files
OBJS = $(SRCS:.c=.o)

# -------------------------
# Default target
# -------------------------
all: $(TARGET)

# -------------------------
# Link object files
# -------------------------
$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJS)

# -------------------------
# Compile each .c → .o
# -------------------------
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# -------------------------
# Run program
# -------------------------
run: $(TARGET)
	./$(TARGET)

# -------------------------
# Clean build files
# -------------------------
clean:
	rm -f $(OBJS) $(TARGET)