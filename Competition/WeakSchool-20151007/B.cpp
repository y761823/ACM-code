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

const int MAXV = 50010;
const int MAX_LOG = 30;

double suma, sumb, sumc;
int a[MAXV], cnt[MAX_LOG];
int n, T;

void solve() {
    suma = sumb = sumc = 0;

    memset(cnt, 0, sizeof(cnt));
    for(int i = 0; i < n; ++i) {
        for(int k = 0; k < MAX_LOG; ++k) {
            if((a[i] >> k) & 1) {
                suma += (LL)++cnt[k] * (1 << k);
            } else {
                cnt[k] = 0;
            }
        }
    }

    memset(cnt, 0, sizeof(cnt));
    for(int i = 0; i < n; ++i) {
        for(int k = 0; k < MAX_LOG; ++k) {
            if((a[i] >> k) & 1) {
                sumb += (LL)(i + 1) * (1 << k);
                cnt[k] = i + 1;
            } else {
                sumb += (LL)cnt[k] * (1 << k);
            }
        }
    }

    memset(cnt, 0, sizeof(cnt));
    for(int i = 0; i < n; ++i) {
        for(int k = 0; k < MAX_LOG; ++k) {
            if((a[i] >> k) & 1) {
                sumc += (LL)(i - cnt[k] + 1) * (1 << k);
                cnt[k] = i - cnt[k] + 1;
            } else {
                sumc += (LL)cnt[k] * (1 << k);
            }
        }
    }
}

int main() {
    scanf("%d", &T);
    for(int t = 1; t <= T; ++t) {
        scanf("%d", &n);
        for(int i = 0; i < n; ++i) scanf("%d", &a[i]);
        solve();
        double v = (LL)n * (n + 1) / 2;
        printf("Case #%d: %.6f %.6f %.6f\n", t, suma / v, sumb / v, sumc / v);
    }
}
