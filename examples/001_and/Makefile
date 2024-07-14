build: and_test.out

%.o: %.c *.h
	gcc -c -g -std=c11 -pedantic -Wall -Wextra -Wshadow -I../../include -o $@ $<

liband.a: and.o
	ar rcs $@ $^

and_test.out: and_test.o liband.a ../../lib/libohcp.a
	gcc -g -o $@ $^

run: and_test.out
	./$<
