all: ftcs crank-nicolson

ftcs:
	cc ftcs.c -O2 -lm -Wall && ./a.out && rm a.out

crank-nicolson:
	cc crank-nicolson.c -lm -Wall && ./a.out > crank-nicolson.dat && rm a.out

