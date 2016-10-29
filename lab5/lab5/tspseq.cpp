//--------------------------------------------------------------------
// Jeremy Kemery
// tspseq.cpp
// 10/20/2016
//--------------------------------------------------------------------

#include <time.h>
#include <iostream>
#include <fstream>

using std::cin;
using std::cout;
using std::cerr;
using std::endl;
using std::string;
using std::ifstream;

//--------------------------------------------------------------------

// maximum number of elements to permute
const int SIZE = 20;

// use a class to hold the Array since Grand Central Dispatch blocks can't modify an array
class Array {
public:
    int items[SIZE];
    int weight;
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
void permute(Array a, int i, int n, short numCities, int pathWeights[][SIZE], Array &shortestPath)
{
    int j;
    // basecase
    // output after permuting all elements
    if (i == n) {
        int pathWeight = pathWeights[0][a.items[0]];
        for (int k=0; k<n; ++k) {
            pathWeight += pathWeights[a.items[k]][a.items[k+1]];
        }
        pathWeight += pathWeights[a.items[n]][0];

        // record path info if shortest path so far
        if (shortestPath.weight > pathWeight) {
            shortestPath.weight = pathWeight;
            for (int k=0; k<=n; ++k) {
                shortestPath.items[k] = a.items[k];
            }
        }
    }
    else {
        // for each element starting at position i, permute those elements
        for (j = i; j <= n; j++) {
            swap(a.items[i], a.items[j]);
            // recursively permute the rest of the itmes after i
            permute(a, i+1, n, numCities, pathWeights, shortestPath);
            // swap back and permute other elements
            swap(a.items[i], a.items[j]);
        }
    }
}

//--------------------------------------------------------------------

void readFile(string fname, unsigned short &numCities, int pathWeights[][SIZE])
{

    ifstream ifs;
    ifs.open(fname.c_str());

    ifs >> numCities;

    // read in matrix
    for (int i=0; i<numCities; i++) {
        for (int j=0; j<numCities; j++) {
            ifs >> pathWeights[i][j];
            cout << pathWeights[i][j] << " ";
        }
        cout << endl;
    }

    ifs.close();
}

//--------------------------------------------------------------------

int main(int argc, char * const argv[])
{
    string fname;
    unsigned short numCities;
    int pathWeights[SIZE][SIZE];

    if (argc == 2) {
        fname = string(argv[1]);
    }
    else {
        fname = "/Users/jeremykemery1/Desktop/sample.txt";
    }

    readFile(fname, numCities, pathWeights);

    cout << endl;

    Array a, shortestPath;
    // fill in values 1 through 20
    for (int i=0; i<SIZE; ++i) {
        a.items[i] = i+1;
    }

    // shortestPath is max int so algorithm works
    shortestPath.weight = INT_MAX;

    // find permutations of path
    time_t start, stop;
    start = time(&start);
    permute(a, 0, numCities - 2, numCities, pathWeights, shortestPath);
    stop = time(&stop);
    cout << "sequential time for " << numCities << ": " << difftime(stop, start) << endl;

    cout << shortestPath.weight << endl;
    cout << "0" << " ";
    for (int i=0; i<numCities - 1; i++) {
        cout << shortestPath.items[i] << " ";
    }
    cout << "0" << endl;

    return 0;
}

//--------------------------------------------------------------------

