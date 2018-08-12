#include <cstdio>
#include <iostream>
#include <algorithm>
#include <cstring>
#include <cmath>
#include <numeric>
using namespace std;
typedef long long LL;

const int MAXN = 300010;
const int INF = 0x3f3f3f3f;

int a[MAXN];
int n, T;

bool check(int target) {
    LL pp = 0, sub = 0;
    for (int i = 0; i < n; ++i) {
        if (a[i] <= target)
            pp += target - a[i];
        else
            sub += (a[i] - target) / 2;
    }
    return pp <= sub;
}

int solve() {
    int l = 1, r = *max_element(a, a + n) + 1;
    while (l < r) {
        int mid = l + (r - l) / 2;
        if (check(mid)) l = mid + 1;
        else r = mid;
    }
    return l - 1;
}

int main() {
    scanf("%d", &T);
    while (T--) {
        scanf("%d", &n);
        for (int i = 0; i < n; ++i)
            scanf("%d", &a[i]);
        printf("%d\n", solve());
    }
}
