CC = gcc
CFLAGS = -Wall -Wextra -g -I.

SRC = main.c display.c event_core.c fileio.c search_algorithms.c
OBJ = $(SRC:.c=.o)

OUT_DIR = output
TARGET = $(OUT_DIR)/smart_calendar

all: $(OUT_DIR) $(TARGET)

$(OUT_DIR):
	mkdir -p $(OUT_DIR)

$(TARGET): $(OBJ)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJ)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

run: all
	./$(TARGET)

clean:
	rm -f *.o $(TARGET)
