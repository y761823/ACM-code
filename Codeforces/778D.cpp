#include <cstdio>
#include <iostream>
#include <cstring>
#include <algorithm>
using namespace std;

typedef long long LL;

const int MAXN = 200010;

char t[MAXN], p[MAXN];
int a[MAXN];
int n;

int check(int cnt) {
    int pos = 0;
    for (char *y = p; *y; ++y) {
        while (pos < n && (a[pos] <= cnt || t[pos] != *y))
            ++pos;
        if (pos++ == n)
            return false;
    }
    return true;
}

int solve() {
    int l = 1, r = n + 1;
    while (l < r) {
        int mid = (l + r) >> 1;
        if (check(mid)) l = mid + 1;
        else r = mid;
    }
    return l - 1;
}

int main () {
    scanf("%s%s", t, p);
    n = strlen(t);
    for (int i = 0, tmp; i < n; ++i) {
        scanf("%d", &tmp);
        a[tmp - 1] = i + 1;
    }
    printf("%d\n", solve());
}
