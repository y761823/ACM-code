#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;

typedef long long LL;

const int MAXN = 100010;
const int MAXA = 1010;
const int MAXB = 12;
const int MAXM = 1010;

int _dp[MAXB][MAXA];
int life[MAXN], def[MAXN], skill[MAXM], damage[MAXM];
int n, m;

void init(int minb, int maxb, int maxlife) {
    for (int b = minb; b <= maxb; ++b) {
        int* dp = _dp[b];
        memset(dp + 1, 0x3f, sizeof(int) * maxlife);
        for (int i = 0; i < m; ++i) if (damage[i] > b) {
            int ski = skill[i], dam = damage[i] - b;
            for (int a = 1; a <= dam; ++a)
                dp[a] = min(dp[a], ski);
            for (int a = dam + 1; a <= maxlife; ++a)
                dp[a] = min(dp[a], dp[a - dam] + ski);
        }
    }
}

LL solve() {
    int minb = *min_element(def, def + n);
    int maxb = *max_element(def, def + n);
    int maxlife = *max_element(life, life + n);
    int maxskill = *max_element(damage, damage + m);
    if (maxskill <= maxb)
        return -1;

    init(minb, maxb, maxlife);

    LL res = 0;
    for (int i = 0; i < n; ++i) {
        res += _dp[def[i]][life[i]];
    }
    return res;
}

int main() {
    while (scanf("%d%d", &n, &m) != EOF) {
        for (int i = 0; i < n; ++i)
            scanf("%d%d", &life[i], &def[i]);
        for (int i = 0; i < m; ++i)
            scanf("%d%d", &skill[i], &damage[i]);
        cout << solve() << endl;
    }
}
