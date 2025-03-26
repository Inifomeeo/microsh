CC = gcc
CFLAGS = -Wall -Wextra

SRC = $(wildcard *.c)
OBJ = $(SRC:.c=.o)
EXEC = shell

all: $(EXEC)

$(EXEC): $(OBJ)
	$(CC) $(OBJ) -o $(EXEC)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ) $(EXEC)

.PHONY: all clean
