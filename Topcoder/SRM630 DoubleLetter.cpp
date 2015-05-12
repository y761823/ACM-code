#include <cstring>
#include <cstdio>
#include <algorithm>
#include <vector>
#include <string>
#include <iostream>
#include <sstream>
#include <stack>
using namespace std;
typedef long long LL;

class DoubleLetter
{
    public:
    string ableToSolve(string s)
    {
        stack<char> stk;
        for(char c : s) {
            if(!stk.empty() && stk.top() == c)
                stk.pop();
            else
                stk.push(c);
        }
        return stk.empty() ? "Possible" : "Impossible";
    }
};
