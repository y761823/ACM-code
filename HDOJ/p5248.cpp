#include <cstdio>
#include <algorithm>
#include <iostream>
#include <cstring>
using namespace std;
typedef long long LL;

const int MAXN = 100010;
const int INF = 0x3f3f3f3f;

int a[MAXN];
int T, n;

bool check(int k) {
    int last = -INF;
    for(int i = 0; i < n; ++i) {
        if(a[i] + k <= last) return false;
        last = max(last + 1, a[i] - k);
    }
    return true;
}

int solve() {
    int l = 0, r = 1000000;
    while(l < r) {
        int mid = (l + r) >> 1;
        if(!check(mid)) l = mid + 1;
        else r = mid;
    }
    return l;
}

int main() {
    scanf("%d", &T);
    for(int t = 1; t <= T; ++t) {
        scanf("%d", &n);
        for(int i = 0; i < n; ++i) scanf("%d", &a[i]);
        printf("Case #%d:\n", t);
        printf("%d\n", solve());
    }
}
