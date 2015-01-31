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
int* cache = new int[3000001];


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
    assert (i>=0 && i<=1000000);
    assert (j>=0 && j<=1000000);

    // Input sorting: compare the inputs and set the larger on as end and the smaller one as start.
    int highest = 0, start, end;
    if(i<j)
    {
        start = (int)i;
        end = j;
    }
    else
    {
        start = (int)j;
        end = i;
    }
    cache[1] = 1;
    
    // iterate through all numbers between start and end
    for(; start<=end; start++)
    {
        int temp = start;
        int cycle = collatz_iter(temp);

        if(start < 3000001 && cache[start] != 0)
        {
            cache[start] = cycle;
        }
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

int collatz_iter (int x)
{
    int cycle = 0;
    while(x>0)
    {
        if(x < 3000001)
        {
            if(cache[x]!=0)
            {
                cycle += cache[x];
                break;
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

// ------------
// collatz_recur
// ------------

int collatz_recur (int x)
{
    if(x == 0)
    {
        // cout << "case [0]: return 0" << endl;
        return 0;
    }
    else if(x < 3000001)
    {
        if(cache[x]!=0)
        {
            // cout << "case [cache found]: return cache["<< x << "]" << endl;
            return cache[x];
        }
        else if(x == 1)
        {
            // cout << "case [x<arr & x=1]: return 1" << endl;
            return 1;
        }
        else if(x & 1)
        {
            // cout << "case [x="<< x <<"<length]: recurr odd case" << endl;
            return cache[x] = 1+collatz_recur(x*3+1);
        }
        else
        {
            // cout << "case [x="<< x <<"<length]: recurr even case" << endl;
            return cache[x] = 1+collatz_recur(x/2);
        }
    }
    else if(x & 1)
    {
        // cache[x] = 1+collatz(x*3+1);
        // cout << "case [x="<< x <<">length]: recurr odd case" << endl;
        return 1+collatz_recur(x*3+1);
    }
    else
    {
        // cache[x] = 1+collatz(x/2);
        // cout << "case [x="<< x <<">length]: recurr even case" << endl;
        return 1+collatz_recur(x/2);
    }
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