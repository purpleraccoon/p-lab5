//--------------------------------------------------------------------
// Dave Reed
// permute.cpp
// 10/08/2014
//--------------------------------------------------------------------

#include <time.h>
#include <iostream>
using std::cin;
using std::cout;
using std::cerr;
using std::endl;

//--------------------------------------------------------------------

// maximum number of elements to permute
const int SIZE = 20;

// use a class to hold the Array since Grand Central Dispatch blocks can't modify an array
class Array {
public:
    int items[SIZE];
};

//--------------------------------------------------------------------

// pass by reference swap function
inline void swap(int &a, int &b)
{
    int temp = a;
    a = b;
    b = temp;
}

//--------------------------------------------------------------------
// recursive permute function
// permutes the n items in parameter a starting at position i
void permute(Array a, int i, int n)
{
    int j;
    // basecase
    // output after permuting all elements
    if (i == n) {
        for (int k=0; k<=n; ++k)
            cout << a.items[k] << " ";
        cout << endl;
    }
    else {
        // for each element starting at position i, permute those elements
        for (j = i; j <= n; j++) {
            swap(a.items[i], a.items[j]);
            // recursively permute the rest of the itmes after i
            permute(a, i+1, n);
            // swap back and permute other elements
            swap(a.items[i], a.items[j]);
        }
    }
}

//--------------------------------------------------------------------

int main (int argc, char * const argv[]) {
    
    Array a;
    // fill in values 1 through 20
    for (int i=0; i<20; ++i) {
        a.items[i] = i+1;
    }
    // sample permutation
    permute(a, 0, 3);
    return 0;
}

//--------------------------------------------------------------------

