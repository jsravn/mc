/*
 * Simple macros for unit testing. Adapted from the minunit framework located
 * at http://www.jera.com/techinfo/jtns/jtn002.html.
 *
 * Copyright 2008 James Ravn
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */
#ifndef MINUNIT_H
#define MINUNIT_H

#include <stdio.h>

#define mu_assert(message, test) do { if (!(test)) return message; } while (0)
#define mu_run(test) do { char *message = test(); tests_run++;	\
		          if (message) return message; } while (0)
#define mu_run_all(tests) do { \
		char *result = tests(); \
		if (result != 0) { \
			printf("Fail: %s\n", result); \
		} else { \
			printf("ALL TESTS PASSED\n"); \
		} \
		printf("Tests run: %d\n", tests_run); \
		if (result) return result != 0; \
	} while (0)

extern int tests_run;

typedef char *mu_test;

#endif
