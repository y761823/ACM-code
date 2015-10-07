#include <cstdio>
#include <iostream>
#include <algorithm>
#include <cstring>
#include <cmath>
#include <complex>
using namespace std;
typedef long long LL;
#define REP(i, n) for(int i = 0; i < n; ++i)
#define foreach(it, vec) for(__typeof(vec.begin()) it = vec.begin(); it != vec.end(); ++it)

int n, m, q, x, T;

int cross(int x, int y, int n) {
    x = min(x, n); y = min(y, n);
    return max(0, x - (n - y));
}

int solve(int n, int m, int x) {
    if(x <= 1) return 0;
    if(x == 2) return 1;
    if(x > n + m) return 0;

    x--;
    n = min(n, x); m = min(m, x);
    if(x & 1) {
        int mid = (x + 1) >> 1;
        return cross(n, m - mid, mid - 1) + cross(n - mid, m, mid - 1) + (n >= mid && m >= mid);
    } else {
        int mid = x >> 1;
        return cross(n, m - mid, mid) + cross(n - mid, m, mid);
    }
}

int main() {
    scanf("%d", &T);
    for(int t = 1; t <= T; ++t) {
        scanf("%d%d%d", &n, &m, &q);
        if(n > m) swap(n, m);
        printf("Case #%d:\n", t);
        while(q--) {
            scanf("%d", &x);
            printf("%d\n", solve(n, m, x));
        }
    }
}
