#include <iostream>
#include <fstream>
#include <string>
#include <chrono>
#include "LinearSystem.h"
#include "test_generator.cpp"

using namespace std;

#define endl '\n'
#define TEST "test.txt"

int main()
{
    char c;
    do
    {
        cout << "Generate a random test? [Y]es/[N]o: ";
        cin >> c;
    }
    while (c != 'Y' && c != 'N');

    if(c == 'Y')
    {
        int n;
        cout << "Insert number of equations: ";
        cin >> n;

        writeRandomTest(n, TEST);
    }

    cout << "Equations are taken from the test.txt file \n";

    ifstream in("test.txt");
    string eq;
    vector<Equation> Eqs;

    while (getline(in, eq) && !eq.empty())
    {
        Eqs.push_back(Equation(eq));
    }

    LinearSystem system(Eqs);

    chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();
    map<string, double> sol = system.solve();
    chrono::steady_clock::time_point end = std::chrono::steady_clock::now();

    for (auto it : sol)
    {
        cout << it.first << " = " << it.second << endl;
    }

    cout << "==================================" << endl;
    cout << "Time taken = " << chrono::duration_cast<std::chrono::microseconds>(end - begin).count()/1000.0 << " milliseconds" << endl;
    cout << "==================================" << endl;

    /*
   int n;
   cin >> n;
   writeRandomTest(n, "test.txt");*/
}