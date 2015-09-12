#include <cstdio>
#include <algorithm>
#include <iostream>
#include <cstring>
#include <cctype>
#include <bitset>
using namespace std;
typedef long long LL;
#define REP(i, n) for(int i = 0; i < n; ++i)

const int MAXN = 200010;

bitset<MAXN> abit, aabit;
int a[MAXN], b[MAXN];
bool exist[MAXN];
int n, m;

int readint() {
    char c = getchar();
    while(!isdigit(c)) c = getchar();
    int res = 0;
    while(isdigit(c)) res = res * 10 + c - '0', c = getchar();
    return res;
}

int main() {
    while(scanf("%d", &n) != EOF) {
        abit.reset();
        for(int i = 0; i < n; ++i)
            abit.set(a[i] = readint());
        aabit = abit;
        for(int i = 0; i < n; ++i)
            aabit |= abit << a[i];

        m = readint();
        int res = 0;
        for(int i = 0; i < m; ++i)
            res += aabit[readint()];
        printf("%d\n", res);
    }
}
