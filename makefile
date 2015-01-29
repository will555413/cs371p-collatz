all:

Collatz.log:
	git log > Collatz.log

Doxyfile:
	doxygen -g

html: Doxyfile Collatz.h Collatz.c++ RunCollatz.c++ TestCollatz.c++
	doxygen Doxyfile

RunCollatz: Collatz.h Collatz.c++ RunCollatz.c++
	g++-4.7 -pedantic -std=c++11 -Wall Collatz.c++ RunCollatz.c++ -o RunCollatz

RunCollatz.out: RunCollatz RunCollatz.in
	RunCollatz < RunCollatz.in > RunCollatz.out

RunCollatz.tmp: RunCollatz RunCollatz.in
	RunCollatz < RunCollatz.in > RunCollatz.tmp
	diff RunCollatz.tmp RunCollatz.out

TestCollatz: Collatz.h Collatz.c++ TestCollatz.c++
	g++-4.7 -fprofile-arcs -ftest-coverage -pedantic -std=c++11 -Wall Collatz.c++ TestCollatz.c++ -o TestCollatz -lgtest -lgtest_main -lpthread

TestCollatz.out: TestCollatz
	valgrind TestCollatz        >  TestCollatz.out 2>&1
	gcov-4.7 -b Collatz.c++     >> TestCollatz.out
	gcov-4.7 -b TestCollatz.c++ >> TestCollatz.out

clean:
	rm -f *.gcda
	rm -f *.gcno
	rm -f *.gcov
	rm -f RunCollatz
	rm -f RunCollatz.tmp
	rm -f TestCollatz
	rm -f TestCollatz.out
