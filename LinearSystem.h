#ifndef LINSYS_H
#define LINSYS_H

#include <vector> 
#include <string>
#include <map>
#include <cmath>
#include "Equation.h"

using namespace std;

class LinearSystem
{
private:
    vector<Equation> AugMat;
    void partialPivot(int st);
    int echelonReduce();
    void backSub();
    void printSystem();
    static bool compEq(Equation &x, Equation &y);

public:
    LinearSystem(vector<Equation> _AugMat);
    map<string, double> solve();
    ~LinearSystem();
};


#include "LinearSystem.cpp"

#endif