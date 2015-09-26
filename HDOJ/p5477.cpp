#include <cstdio>
#include <algorithm>
#include <iostream>
#include <cstring>
#include <vector>
using namespace std;
typedef long long LL;

const int MAXN = 110;
const int MOD = 1e9 + 7;

int T, n, A, B, L;

int main() {
    scanf("%d", &T);
    for(int t = 1; t <= T; ++t) {
        scanf("%d%d%d%d", &n, &A, &B, &L);
        int last = 0, now = 0, res = 0;
        for(int i = 0, x, y; i < n; ++i) {
            scanf("%d%d", &x, &y);
            now += (x - last) * B - (y - x) * A;
            res = min(now, res);
            last = y;
        }
        printf("Case #%d: %d\n", t, -res);
    }
}
