# Makefile for compiling MC tests.
#
# Copyright 2008 James Ravn
#
# This program is free software: you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation, either version 3 of the License, or
# (at your option) any later version.
#
# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
# You should have received a copy of the GNU General Public License
# along with this program.  If not, see <http://www.gnu.org/licenses/>.

CC = gcc
CFLAGS = -Wall -std=c99 -pedantic -g -O2
OBJECTS = mc.o mc_gen.o mc_prng.o mc_mem.o mc_bootstrap.o
LIBS = -lm

test : mc_test mc_gen_test mc_prng_test mc_bootstrap_test
	@for t in $^; do \
	  echo "Running ./$$t..."; ./$$t; echo ""; \
	done

%_test : $(OBJECTS) %_test.o
	$(CC) $(CFLAGS) $^ $(LIBS) -o $@

%.o : %.c
	$(CC) $(CFLAGS) -c $<

.PHONY: clean
clean :
	rm -f *.o *_test *.exe
