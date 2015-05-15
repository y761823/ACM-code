#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
#define FOR(i, n) for(int i = 0; i < n; ++i)

const int MAXN = (1 << 20) + 10;

int gray(int x) {
    return x ^ (x >> 1);
}

int n, m;

int main() {
    scanf("%d%d", &n, &m);
    for(int i = 0; i < (1 << n); ++i) {
        for(int j = 0; j < (1 << m); ++j)
            printf("%d ", (gray(i) << m) | (gray(j)));
        puts("");
    }
}
