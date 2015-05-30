#include <cstdio>
#include <algorithm>
#include <iostream>
#include <cstring>
#include <vector>
#include <set>
using namespace std;
typedef long long LL;

const int MAXN = 10010;
const int INF = 0x3f3f3f3f;

LL a[MAXN];
int n, m, k;

vector<LL> tmp;
LL gethash(LL x) {
    return lower_bound(tmp.begin(), tmp.end(), x) - tmp.begin();
}
void inithash() {
    for(int i = 0; i < n; ++i)
        tmp.push_back(a[i]);
    sort(tmp.begin(), tmp.end());
    tmp.erase(unique(tmp.begin(), tmp.end()), tmp.end());
    for(int i = 0; i < n; ++i)
        a[i] = gethash(a[i]);
}

int logn[MAXN];
LL rmax[16][MAXN], rmin[16][MAXN];

void initRMQ() {
    logn[0] = -1;
    for(int i = 1; i <= n; ++i)
        logn[i] = (i & (i - 1)) == 0 ? logn[i - 1] + 1 : logn[i - 1];
    for(int i = 0; i < n; ++i) rmax[0][i] = rmin[0][i] = a[i];
    for(int i = 1; i <= logn[n]; ++i) {
        int ed = n - (1 << i) + 1;
        for(int j = 0; j < ed; ++j) {
            rmin[i][j] = min(rmin[i - 1][j], rmin[i - 1][j + (1 << (i - 1))]);
            rmax[i][j] = max(rmax[i - 1][j], rmax[i - 1][j + (1 << (i - 1))]);
        }
    }
}

LL get_diff(int a, int b) {
    int t = logn[b - a + 1];
    return max(rmax[t][a], rmax[t][b - (1 << t) + 1]) - min(rmin[t][a], rmin[t][b - (1 << t) + 1]);
}

int cnt[MAXN];

int solve() {
    int res = 0, flag = 0;
    for(int i = 0; i < n; ++i) {
        if(i - k >= 0) {
            flag -= (cnt[a[i - k]] == 1);
            flag += (--cnt[a[i - k]] == 1);
        }

        flag -= (cnt[a[i]] == 1);
        flag += (++cnt[a[i]] == 1);

        if(flag == k && get_diff(i - k + 1, i) == k - 1)
            res++;
    }
    for(int i = n - k; i < n; ++i)
        --cnt[a[i]];
    return res;
}

int main() {
    scanf("%d%d", &n, &m);
    for(int i = 0; i < n; ++i) scanf("%I64d", &a[i]);
    initRMQ();
    inithash();
    puts("Case #1:");
    for(int i = 0; i < m; ++i) {
        scanf("%d", &k);
        printf("%d\n", solve());
    }
}
