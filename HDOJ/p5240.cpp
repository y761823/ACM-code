#include <cstdio>
#include <iostream>
#include <algorithm>
#include <cstring>
#include <vector>
using namespace std;
typedef long long LL;

const int MAXN = 100010;

struct Node {
    int r, e, l;
    void read() {
        scanf("%d%d%d", &r, &e, &l);
    }
    bool operator < (const Node &rhs) const {
        return e < rhs.e;
    }
} a[MAXN];
int T, n, m;

bool solve() {
    sort(a, a + n);
    int rest = 0, pos = 0;
    for(int i = 0; i < n; ++i) {
        rest += a[i].e - pos;
        if(rest < a[i].r) return false;
        rest -= a[i].r;
        pos = a[i].e + a[i].l;
    }
    return true;
}

int main() {
    scanf("%d", &T);
    for(int t = 1; t <= T; ++t) {
        scanf("%d", &n);
        for(int i = 0; i < n; ++i) a[i].read();
        printf("Case #%d: %s\n", t, solve() ? "YES" : "NO");
    }
}
