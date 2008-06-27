#ifndef MINUNIT_H
#define MINUNIT_H

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
