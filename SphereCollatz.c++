// -------------------------------
// projects/collatz/SphereCollatz.c++
// Copyright (C) 2015
// Glenn P. Downing
// -------------------------------

// -------
// defines
// -------

#ifdef ONLINE_JUDGE
    #define NDEBUG
#endif

// --------
// includes
// --------

#include <iostream> // cin, cout, endl, istream, ostream
#include <cassert>  // assert
#include <sstream>  // istringstream
#include <string>   // getline, string
#include <utility>  // make_pair, pair

using namespace std;

// ----
// declare methods
// ----

pair<int, int> collatz_read (const string& s);
int collatz_eval (int i, int j);
void collatz_print (ostream& w, int i, int j, int v);
void collatz_solve (istream& r, ostream& w);

// ----
// main
// ----

int main () {
    using namespace std;
    collatz_solve(cin, cout);
    return 0;}

// ------------
// collatz_read
// ------------

pair<int, int> collatz_read (const string& s) {
    istringstream sin(s);
    int i;
    int j;
    sin >> i >> j;
    return make_pair(i, j);}

// ------------
// collatz_eval
// ------------

int collatz_eval (int i, int j) {
    // assert: input validity check
    assert (i>0 && i<=1000000);
    assert (j>0 && j<=1000000);

    int highest = 0, start, end;
    if(i<j)
    {
        start = i;
        end = j;
    }
    else
    {
        start = j;
        end = i;
    }
    
    for(; start<=end; start++)
    {
        // int iter = collatz(start);
        int temp = start, cycle = 1;
        while(temp!=1)
        {
            if(temp % 2 == 1)
                temp = (temp*3+1);
            else
                temp = temp/2;
            cycle++;
        }
        if(highest<cycle)
            highest = cycle;
    }
    // assert: output validity check
    assert (highest>0);
    return highest;
}

// -------------
// collatz_print
// -------------

void collatz_print (ostream& w, int i, int j, int v) {
    w << i << " " << j << " " << v << endl;}

// -------------
// collatz_solve
// -------------

void collatz_solve (istream& r, ostream& w) {
    string s;
    while (getline(r, s)) {
        const pair<int, int> p = collatz_read(s);
        const int            i = p.first;
        const int            j = p.second;
        const int            v = collatz_eval(i, j);
        collatz_print(w, i, j, v);}}