#include <cstdio>
#include <algorithm>
#include <iostream>
#include <cstring>
using namespace std;
typedef long long LL;

const int MAXN = 10010;

LL a[MAXN];
int T, n, m, k;

bool solve() {
    int v = 0;
    LL f = m;
    for(int i = k; i >= 0; --i) {
        if(v == n || a[v] > f) break;
        while(v < n && a[v] <= f) ++v;
        f = a[v - 1] + i;
    }
    return v == n;
}

int main() {
    scanf("%d", &T);
    for(int t = 1; t <= T; ++t) {
        scanf("%d%d%d", &n, &m, &k);
        for(int i = 0; i < n; ++i) scanf("%I64d", &a[i]);
        sort(a, a + n);
        printf("Case #%d:\n", t);
        puts(solve() ? "why am I so diao?" : "madan!");
    }
}
