#include <cstdio>
#include <cstring>
#include <algorithm>
#include <iostream>
using namespace std;

const int MAXN = 20010;
const int MAXK = 1000010;

int s[MAXN], n, k;
int sa[MAXN], rank[MAXN], tmp[MAXN], height[MAXN];
int c[MAXK];

void makesa(int m) {
    memset(c, 0, sizeof(c));
    for(int i = 0; i < n; ++i) ++c[rank[i] = s[i]];
    for(int i = 1; i < m; ++i) c[i] += c[i - 1];
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
    }
}

void calheight() {
    for(int i = 0, k = 0; i < n; height[rank[i++]] = k) {
        if(k > 0) --k;
        int j = sa[rank[i] - 1];
        while(s[i + k] == s[j + k]) ++k;
    }
}

bool check(int L) {
    int cnt = 1;
    for(int i = 1; i < n; ++i) {
        if(height[i] >= L) {
            if(++cnt >= k) return true;
        } else {
            cnt = 1;
        }
    }
    return cnt >= k;
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
    scanf("%d%d", &n, &k);
    for(int i = 0; i < n; ++i) scanf("%d", &s[i]), ++s[i];
    s[n++] = 0;
    makesa(MAXK);
    calheight();
    printf("%d\n", solve());
}
