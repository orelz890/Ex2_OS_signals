
all: run
run: sig_loop
	./signal_loop.out
sig_loop: signal_loop.c
	gcc -o signal_loop.out signal_loop.c

clean:
	rm -f *.out

PHONY: all clean
