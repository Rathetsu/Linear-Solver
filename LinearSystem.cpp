#include "LinearSystem.h"
#define endl '\n'

LinearSystem::LinearSystem(vector<Equation> _AugMat)
{
    AugMat = _AugMat;
}

void LinearSystem::partialPivot(int st)
{
    sort(AugMat.begin() + st, AugMat.end(), compEq);
}

bool LinearSystem::compEq(Equation &x, Equation &y)
{
    return abs(x.getPivot().coff) > abs(y.getPivot().coff);
}

int LinearSystem::echelonReduce()
{
    int t;
    for (int i = 0; i < AugMat.size(); ++i)
    {
        partialPivot(i);
        Equation &A = AugMat[i];
        Term pivotA = A.getPivot();
        if (pivotA.coff == 0)
        {
            cout << "System has no or infinitely many solutions" << endl;
            return 0;
        }
        for (int j = i + 1; j < AugMat.size(); ++j)
        {
            Equation &B = AugMat[j];
            double coffB = B.getCoff(pivotA.symbol);
            B = B - (coffB / pivotA.coff) * A;
        }
    }
    return 1;
}

void LinearSystem::backSub()
{

    map<string, double> subList;

    for (int i = AugMat.size() - 1; i >= 1; --i)
    {
        Equation &E = AugMat[i];
        Term pivot = E.getPivot();
        subList[pivot.symbol] = E.getConst() / pivot.coff;
        for (int j = i - 1; j >= 0; --j)
        {
            AugMat[j].substitute(subList);
        }
    }
}

void LinearSystem::printSystem()
{

    for (auto it: AugMat)
    {
        cout << it;
    }
}

map<string, double> LinearSystem::solve()
{
    map<string, double> sol;
    int res = echelonReduce();
    //cout << "RREF Done" << endl;
    //printSystem();
    
    if (res == 1)
    {
        backSub();

        for (auto it : AugMat)
        {
            Term pivot = it.getPivot();
            sol[pivot.symbol] = it.getConst()/pivot.coff;
        }
    }

    return sol;
}


LinearSystem::~LinearSystem()
{
}