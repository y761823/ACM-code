#include <cstdio>
#include <algorithm>
#include <iostream>
#include <cstring>
#include <queue>
using namespace std;
typedef long long LL;
#define REP(i, n) for(int i = 0; i < n; ++i)

const int MAXN = 1010;

int a[MAXN], n, q, T;

int main() {
    scanf("%d", &T);
    while(T--) {
        scanf("%d", &n);
        for(int i = 1; i <= n; ++i)
            scanf("%d", &a[i]);
        scanf("%d", &q);
        for(int i = 0, l, r; i < q; ++i) {
            scanf("%d%d", &l, &r);
            printf("%d\n", *max_element(a + l, a + r + 1));
        }
    }
}
