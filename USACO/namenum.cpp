/*
ID: y7618231
PROG: namenum
LANG: C++
*/
#ifdef OYK_JUDGE
#define longformat "%I64d"
#else
#define longformat "%lld"
#endif // OYK_JUDGE

#include <iostream>
#include <string>
#include <cstdio>
#include <cstring>
#include <vector>
using namespace std;

char op[][3] = {{'A','B','C'}, {'D','E','F'}, {'G','H','I'}, {'J','K','L'}, {'M','N','O'}, {'P','R','S'}, {'T','U','V'}, {'W','X','Y'}};

vector<string> vec;

void get_dictionary();
bool flag;
char s[20], n;

void dfs(int dep, string ans) {
    if(dep == n) {
        vector<string>::iterator it = lower_bound(vec.begin(), vec.end(), ans);
        if(it != vec.end() && *it == ans)
            puts(ans.c_str()), flag = true;
    } else {
        for(int i = 0; i < 3; ++i) {
            if(s[dep] < '2' || s[dep] > '9') return ;
            char c = op[s[dep] - '2'][i];
            dfs(dep + 1, ans + c);
        }
    }
}

int main() {
    get_dictionary();
#ifndef OYK_JUDGE
    freopen("namenum.in", "r", stdin); freopen("namenum.out", "w", stdout);
#endif
    scanf("%s", s);
    n = strlen(s);
    dfs(0, "");
    if(!flag) puts("NONE");
}

void get_dictionary() {
    FILE *f = fopen("dict.txt", "r");
    while(fscanf(f, "%s", s) != EOF)
        vec.push_back(s);
}
