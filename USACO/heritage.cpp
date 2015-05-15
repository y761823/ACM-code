/*
ID: y7618231
PROG: heritage
LANG: C++11
*/
#ifdef OYK_JUDGE
#define longformat "%I64d"
#else
#define longformat "%lld"
#endif // OYK_JUDGE

#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <numeric>
#include <queue>
#include <tuple>
using namespace std;
typedef long long LL;
#define FOR(i, s, t) for(int i = s; i <= t; ++i)

const int MAXN = 33;

char pre[MAXN], infix[MAXN], post[MAXN];

void build(int &p, char *infix_st, char *infix_ed) {
    if(infix_st == infix_ed) return ;
    char *mid = strchr(infix_st, pre[p]);
    char c = pre[p++];
    build(p, infix_st, mid);
    build(p, mid + 1, infix_ed);
    putchar(c);
}

int main() {
#ifndef OYK_JUDGE
    freopen("heritage.in", "r", stdin); freopen("heritage.out", "w", stdout);
#endif // OYK_JUDGE
    scanf("%s", infix);
    scanf("%s", pre);
    int t = 0;
    build(t, infix, infix + strlen(infix));
    puts("");
}
