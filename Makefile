CC = cc
CFLAGS = -std=c11 -Wall -Wextra -I.
LDFLAGS = -lm

SRC := $(wildcard *.c)
OBJ := $(patsubst %.c,%.o,$(SRC))

TARGET = pso

all: $(TARGET)

$(TARGET): $(OBJ)
	$(CC) $(CFLAGS) -o $@ $(OBJ) $(LDFLAGS)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

.PHONY: clean run

run: $(TARGET)
	./$(TARGET)

clean:
	rm -f $(TARGET) $(OBJ) log.csv
