#include <iostream>
#include <algorithm>
#include <cstring>
#include <cstdio>
using namespace std;

const int MAXN = 100010;
const int MAXC = 26;

char str[MAXN];
int cnt[MAXC][MAXN];
int T, n, q;

void init() {
    memset(cnt, 0, sizeof(cnt));
    for (int i = 1; i <= n; ++i)
        cnt[str[i] - 'A'][i] = 1;
    for (int i = 0; i < MAXC; ++i)
        for (int j = 1; j < n; ++j)
            cnt[i][j + 1] += cnt[i][j];
}

int solve(int l, int r) {
    for (int i = 0; i < MAXC; ++i)
        if (cnt[i][r] - cnt[i][l - 1] > 0)
            return cnt[i][r] - cnt[i][l - 1];
    return 0;
}

int main() {
    scanf("%d", &T);
    for (int t = 1; t <= T; ++t) {
        scanf("%d%d", &n, &q);
        scanf("%s", str + 1);
        init();
        printf("Case #%d:\n", t);

        int l, r;
        for (int i = 0; i < q; ++i) {
            scanf("%d%d", &l, &r);
            printf("%d\n", solve(l, r));
        }
    }
}
