build: fifo_test.out

%.o: %.c *.h
	gcc -c -g -std=c11 -pedantic -Wall -Wextra -Wshadow -I../../include -o $@ $<

libfifo.a: fifo.o
	ar rcs $@ $^

fifo_test.out: fifo_test.o libfifo.a ../../lib/libohcp.a
	gcc -g -o $@ $^ -lm

run: fifo_test.out
	./$<
