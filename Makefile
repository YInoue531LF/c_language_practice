PROGRAM = hello
CC = gcc
OBJS = main.o hello.o print.o

$(PROGRAM): $(OBJS)
	$(CC) -Wall -O2 -o $@ $^

%.o: %.c
	$(CC) -c $^

.PHONY:clean
clean:
	rm -f $(PROGRAM) $(OBJS)
