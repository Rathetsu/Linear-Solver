#include "Equation.h"
#include <algorithm>
using namespace std;

#define EPS 1e-5
#define isZero(x) (abs(x) <= EPS)

Equation::Equation(string eq)
{
    terms = parseEquation(eq);
    // Move the constant to the RHS
    terms[""] = -terms[""];
}

Equation::Equation(const map<string, double, greater<string>> &other)
{
    terms = other;
}

void Equation::addTerm(Term term)
{
    terms[term.symbol] = terms[term.symbol] + term.coff;
}

void clearSpaces(string &s)
{
    string t = "";
    for (auto c : s)
    {
        if (c != ' ')
            t += c;
    }
    s = t;
}

map<string, double, greater<string>> Equation::parseEquation(string eq)
{
    clearSpaces(eq);

    if (eq[0] != '+' && eq[0] != '-')
    {
        eq = "+" + eq;
    }

    map<string, double, greater<string>> res;
    size_t equalSignPos = eq.find_first_of("=");

    if (eq[equalSignPos + 1] != '+' && eq[equalSignPos + 1] != '-')
    {
        eq.insert(equalSignPos + 1, "+");
    }
      

    for (int i = equalSignPos + 1; i < eq.size(); ++i)
    {
        if (eq[i] == '+')
        {
            eq[i] = '-';
        }
        else if (eq[i] == '-')
        {
            eq[i] = '+';
        }   
    }
    eq.erase(equalSignPos, 1);
    int st = 0;
    while (st < eq.size())
    {
        string termString = getNextTermString(eq, st);
        Term term = stringToTerm(termString);
        res[term.symbol] += term.coff;
    }

    return res;
}

string Equation::getNextTermString(string seq, int &st)
{
    for (int i = st + 1; i < seq.size(); ++i)
    {
        if (seq[i] == '+' || seq[i] == '-')
        {
            int _st = st;
            st = i;
            return seq.substr(_st, i - _st);
        }
    }
    int _st = st;
    st = seq.size();
    return seq.substr(_st);
}

Term Equation::stringToTerm(string term)
{
    int sign = (term[0] == '-' ? -1 : 1);
    for (int i = 1; i < term.size(); ++i)
    {
        if (term[i] != '.' && !isdigit(term[i]))
        {
            string symbol = term.substr(i);
            double coff = i == 1 ? sign : sign * stod(term.substr(1, i - 1));

            return Term(symbol, coff);
        }
    }
    double coff = sign * stod(term.substr(1));
    return Term("", coff);
}

set<string> varsUnion(const Equation &A, const Equation &B)
{
    set<string> varnames;
    for (auto it : A.terms)
    {
        varnames.insert(it.first);
    }
    for (auto it : B.terms)
    {
        varnames.insert(it.first);
    }
    return varnames;
}

Term Equation::getPivot()
{
    for (auto it : terms)
    {
        if (!isZero(it.second) && it.first != "")
        {
            return Term(it.first, it.second);
        }
    }
    return Term("", 0);
}

double Equation::getCoff(string varname)
{
    return terms[varname];
}

double Equation::getConst()
{
    return terms[""];
}

void Equation::substitute(map<string, double> subs)
{
    for (auto it : subs)
    {
        double c = terms[it.first]*it.second;
        terms[it.first] = 0.0;
        terms[""] -= c;
    }
}

Equation operator*(double coff, Equation A)
{
    map<string, double, greater<string>> newTerms(A.terms);
    for (auto &term : newTerms)
    {
        term.second *= coff;
    }
    return Equation(newTerms);
}

Equation operator+(Equation A, Equation B)
{
    set<string> varnames = varsUnion(A, B);
    for (auto &it : varnames)
    {
        A.terms[it] += B.terms[it];
    }
    return A;
}

Equation operator-(Equation A, Equation B)
{
    set<string> varnames = varsUnion(A, B);
    for (auto &it : varnames)
    {
        A.terms[it] -= B.terms[it];
    }
    return A;
}

ostream &operator<<(ostream &out, const Equation &Eq)
{
    bool firstTerm = true;
    for (auto it : Eq.terms)
    {
        if (it.first != "" && !isZero(it.second))
        {
            if (!firstTerm || it.second < 0)
            {
                out << (it.second > 0 ? "+ " : "- ");
            }
            if(abs(it.second) != 1) out << abs(it.second);
            out << it.first << " ";
            firstTerm = false;
        }
    }
    double constTerm = Eq.terms.find("")->second;
    out << "= " << (constTerm == 0.0? abs(constTerm): constTerm) << endl;
    return out;
}

Equation::~Equation()
{
}