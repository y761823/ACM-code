/*
ID: y7618231
PROG: fence9
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
using namespace std;
typedef long long LL;
#define FOR(i, s, t) for(int i = s; i <= t; ++i)

int n, m, p;
int A, b;

int main() {
#ifndef OYK_JUDGE
    freopen("fence9.in", "r", stdin); freopen("fence9.out", "w", stdout);
#endif // OYK_JUDGE
    scanf("%d%d%d", &n, &m, &p);
    A = p * m;
    b = __gcd(n, m) + __gcd(abs(p - n), m) + p;
    printf("%d\n", (A - b + 2) / 2);
}
