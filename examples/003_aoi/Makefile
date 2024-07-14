build: aoi_test.out

%.o: %.c *.h
	gcc -c -g -std=c11 -pedantic -Wall -Wextra -Wshadow -I../../include -o $@ $<

libaoi.a: aoi.o
	ar rcs $@ $^

aoi_test.out: aoi_test.o libaoi.a ../../lib/libohcp.a
	gcc -g -o $@ $^ -lm

run: aoi_test.out
	./$<
