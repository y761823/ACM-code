#include <cstdio>
#include <algorithm>
#include <iostream>
#include <cstring>
using namespace std;

const int MAXN = 20010;
int s[MAXN];
int n, sa[MAXN], height[MAXN], rank[MAXN], tmp[MAXN], c[MAXN];

void makesa(int m) {
    memset(c, 0, sizeof(c));
    for(int i = 0; i < n; ++i) ++c[rank[i] = s[i]];
    for(int i = 0; i < m; ++i) c[i] += c[i - 1];
    for(int i = 0; i < n; ++i) sa[--c[rank[i]]] = i;
    for(int k = 1; k < n; k <<= 1) {
        for(int i = 0; i < n; ++i) {
            int j = sa[i] - k;
            if(j < 0) j += n;
            tmp[c[rank[j]]++] = j;
        }
        int j = c[0] = sa[tmp[0]] = 0;
        for(int i = 1; i < n; ++i) {
            if(rank[tmp[i]] != rank[tmp[i - 1]] || rank[tmp[i] + k] != rank[tmp[i - 1] + k])
                c[++j] = i;
            sa[tmp[i]] = j;
        }
        memcpy(rank, sa, n * sizeof(int));
        memcpy(sa, tmp, n * sizeof(int));
        if(j >= n - 1) break;
    }
}

void calheight() {
    for(int i = 0, k = 0; i < n; height[rank[i++]] = k) {
        if(k > 0) --k;
        int j = sa[rank[i] - 1];
        while(s[i + k] == s[j + k]) ++k;
    }
}

bool check(int k) {
    int mx = sa[0], mn = sa[0];
    for(int i = 1; i < n; ++i) {
        if(height[i] >= k - 1) {
            mx = max(mx, sa[i]);
            mn = min(mn, sa[i]);
        } else {
            if(mx - mn >= k) return true;
            mx = mn = sa[i];
        }
    }
    return mx - mn >= k;
}

int solve() {
    int l = 1, r = n;
    while(l < r) {
        int mid = (l + r) >> 1;
        if(check(mid)) l = mid + 1;
        else r = mid;
    }
    return l - 1;
}

int main() {
    while(scanf("%d", &n) != EOF && n) {
        for(int i = 0; i < n; ++i) scanf("%d", &s[i]);
        for(int i = 0; i < n - 1; ++i) s[i] = s[i + 1] - s[i] + 88;
        s[n - 1] = 0;
        makesa(176);
        if(n != 1) calheight();
        int ans = solve();
        printf("%d\n", ans >= 5 ? ans : 0);
    }
}
