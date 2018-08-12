#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>
using namespace std;

const int MAXN = 1024 + 10;

int src[MAXN], cnt[MAXN];
int n, m, k, T;

int str2int(char str[]) {
    int res = 0;
    for (char* p = str; *p; ++p)
        res = (res << 1) | (*p == 'B');
    return res;
}

int solve() {
    int res = 0;
    for (int mask = 1; mask < (1 << m); ++mask) {
        memset(cnt, 0, sizeof(int) * (1 << m));
        for (int i = 0; i < n; ++i)
            cnt[src[i] & mask]++;
        int sum = 0;
        for (int i = 0; i < (1 << m); ++i)
            if (cnt[i]) sum += (n - cnt[i]) * cnt[i];
        res += (sum / 2 >= k);
    }
    return res;
}

int main() {
    scanf("%d", &T);
    for (int t = 1; t <= T; ++t) {
        scanf("%d%d%d", &n, &m, &k);
        char str[11];
        for (int i = 0; i < n; ++i) {
            scanf("%s", str);
            src[i] = str2int(str);
        }
        printf("Case #%d: %d\n", t, solve());
    }
}
