#include <string>
#include <iostream>
#include <vector>
#include <fstream>
#include <time.h>

using namespace std;


string allowedChars()
{
    string chars = "";

    for(int i = 0; i < 26; ++i)
    {
        chars += 'a' + i;
    }
    for(int i = 0; i < 26; ++i)
    {
        chars += 'A' + i;
    }
    chars += '_';
    cout << "allowed = " << chars << endl;

    return chars;
    
}

vector<string> randomNames(int n)
{
    vector<string> names;
    string allowed = allowedChars();
    for(int i = 0; i < n; ++i)
    {
        string s;
        s += rand()%26 + 'a';
        int len = rand()%4;
        while(len--)
        {
            s += allowed[rand()%allowed.size()];
        }
        names.push_back(s);
    }
    return names;
}



void writeRandomTest(int n, string filename)
{
    srand(time(NULL));
    ofstream out(filename);
    vector<string> varnames = randomNames(n);
    for(int i = 0; i < n; ++i)
    {
        int numOfTerms = rand()%n + 1;
        string eq="";
        for(int j = 0; j < n; ++j)
        {
            double coff = (rand()&1? -1.0: 1.0)*(rand()/1000.0);
            if(coff > 0.0) 
                eq += '+';
            eq += to_string(coff) + varnames[rand()%n];
        }
        eq += "=" + to_string((rand()&1? -1.0: 1.0)*(rand()/1000.0));

        out << eq << '\n';

    }
    out.close();
}
