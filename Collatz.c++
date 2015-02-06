// ----------------------------
// projects/collatz/Collatz.c++
// Copyright (C) 2015
// Glenn P. Downing
// ----------------------------

// --------
// includes
// --------

#include <cassert>  // assert
#include <iostream> // endl, istream, ostream
#include <sstream>  // istringstream
#include <string>   // getline, string
#include <utility>  // make_pair, pair

#include "Collatz.h"

using namespace std;

// global array that acts like a cache to store the calculated collatz value
int cache [3000001] = {};


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
    assert (i>0 && i<1000000);
    assert (j>0 && j<1000000);

    // Input sorting: compare the inputs and set the larger on as end and the smaller one as start.
    int highest = 0, start = 0, end = 0;
    if(i==j)
    {
        start = i;
        end = i;
    }
    else if(i<j)
    {
        start = (j/2+1>i) ? j/2+1 : i;
        end = j;
    }
    else
    {
        start = (i/2+1>j) ? i/2+1 : j;
        end = i;
    }
    cache[1] = 1;
    
    // iterate through all numbers between start and end
    for(; start<=end; start++)
    {
        int cycle = 0;
        cycle = collatz_iter(start);

        if(start < 3000001 && cache[start] != 0)
        {
            cache[start] = cycle;
        }
        // cout<<"cycle of "<<start<<" = "<<cycle<<endl;
        if(highest<cycle)
            highest = cycle;
    }
    // assert: output validity check
    assert (highest>0);
    return highest;
    // return 1;
}

// ------------
// collatz_iter
// ------------

int collatz_iter (int i)
{
    int cycle = 0;
    unsigned int x = i;
    while(x>0)
    {
        if(x < 3000001)
        {
            if(cache[x]!=0)
            {
                cycle += cache[x];
                return cycle;
            }
        }
        if(x & 1)
        {
            x += (x >> 1) + 1;    
            cycle += 2;
        }
        else
        {
            x = x >> 1;
            cycle++;
        }

    }
    return cycle;
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