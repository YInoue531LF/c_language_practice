PROGRAM = server
OBJS = main.o
CC = gcc

$(PROGRAM): $(OBJS)
	$(CC) -Wall -O2 -o $@ $^

%.o: %.c
	$(CC) -c $^

.PHONY: clear
clear:
	rm -f $(PROGRAM) $(OBJS)
