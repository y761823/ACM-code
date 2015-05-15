/*
ID: y7618231
PROG: hidden
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
#include <vector>
using namespace std;
typedef long long LL;
#define REP(i, n) for(int i = 0; i < n; ++i)
#define FOR(i, s, t) for(int i = s; i <= t; ++i)

const int MAXN = 200010;
const int INF = 0x3f3f3f3f;

char s[MAXN];
int n;

int minRepresentation() {
    memcpy(s + n, s, n * sizeof(char));
    int i = 0, j = 1;
    while(i < n && j < n) {
        int k = 0;
        while(k < n && s[i + k] == s[j + k]) ++k;
        if(k == n) break;
        if(s[i + k] > s[j + k]) i += k + 1;
        else j += k + 1;
        if(i == j) ++j;
    }
    return min(i, j);
}

int main() {
#ifndef OYK_JUDGE
    freopen("hidden.in", "r", stdin); freopen("hidden.out", "w", stdout);
#endif // OYK_JUDGE
    scanf("%*d");
    while(scanf("%s", s + n) != EOF)
        n += strlen(s + n);
    printf("%d\n", minRepresentation());
}
