#include <bits/stdc++.h>
using namespace std;

const int MAXN = 20010;
const int INF = 0x3f3f3f3f;

int a[MAXN];
int T, n, k;

int main() {
    scanf("%d", &T);
    while(T--) {
        scanf("%d%d", &n, &k);
        for(int i = 1; i <= n; ++i) scanf("%d", &a[i]);
        sort(a + 1, a + n + 1);
        int res = INF;
        for(int i = 1; i + k - 1 <= n; ++i)
            res = min(res, a[i + k - 1] - a[i]);
        printf("%d\n", res);
    }
}