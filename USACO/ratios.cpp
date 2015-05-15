/*
ID: y7618231
LANG: C++
TASK: ratios
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

const int MAXN = 365;
const int INF = 0x3f3f3f3f;

int a[4][3];
int s[3];
int ax, ay, az, ap;

void check(int x, int y, int z) {
    for(int i = 0; i < 3; ++i)
        s[i] = x * a[0][i] + y * a[1][i] + z * a[2][i];
    for(int i = 0; i < 3; ++i)
        if(a[3][i] && s[i] % a[3][i] != 0) return ;
    int p = -1;
    for(int i = 0; i < 3; ++i)
        if(a[3][i]) {
            if(p == -1) p = s[i] / a[3][i];
            else if(p != s[i] / a[3][i]) return ;
        } else {
            if(s[i] != 0) return ;
        }
    if(p > 0 && p < ap) ax = x, ay = y, az = z, ap = p;
}

void solve() {
    for(int x = 0; x <= 100; ++x) {
        for(int y = 0; y <= 100; ++y) {
            for(int z = 0; z <= 100; ++z)
                check(x, y, z);
        }
    }
}

int main() {
#ifndef OYK_JUDGE
    freopen("ratios.in", "r", stdin); freopen("ratios.out", "w", stdout);
#endif // OYK_JUDGE
    for(int i = 3; i < 7; ++i)
        for(int j = 0; j < 3; ++j) scanf("%d", &a[i % 4][j]);
    ap = INF;
    solve();
    if(ap != INF) printf("%d %d %d %d\n", ax, ay, az, ap);
    else puts("NONE");
}
