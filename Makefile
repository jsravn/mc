# Makefile for compiling MC tests

CC = gcc
CFLAGS = -Wall -std=c99 -pedantic -g -O2
OBJECTS = mc.o mc_gen.o mc_prng.o mc_mem.o mc_bootstrap.o
LIBS = -lm

test : mc_test mc_gen_test mc_prng_test mc_bootstrap_test
	@for t in $^; do \
	  echo "Running $$t..."; $$t; echo ""; \
	done

%_test : $(OBJECTS) %_test.o
	$(CC) $(CFLAGS) $^ $(LIBS) -o $@

%.o : %.c
	$(CC) $(CFLAGS) -c $<

.PHONY: clean
clean :
	rm -f *.o *_test *.exe
