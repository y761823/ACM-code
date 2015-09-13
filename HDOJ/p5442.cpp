#include <cstdio>
#include <iostream>
#include <cstring>
#include <algorithm>
using namespace std;

const int MAXN = 20010 * 4;

namespace Oyk {

char s[MAXN], a[MAXN];
int sa[MAXN], height[MAXN], rank[MAXN], c[MAXN], tmp[MAXN];
int n, T;

void makesa(int n, int m) {
    memset(c, 0, m * sizeof(int));
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

void calheight(int n) {
    for(int i = 0, k = 0; i < n; height[rank[i++]] = k) {
        if(k > 0) --k;
        int j = sa[rank[i] - 1];
        while(s[i + k] == s[j + k]) ++k;
    }
}

bool cancalc(int pos) {
    return (0 <= pos && pos < n) || (2 * n <= pos && pos < 3 * n);
}

int normal(int x) {
    return x < n ? x : 3 * n - x - 1;
}
int getbest(int x, int y) {
    if(normal(x) != normal(y))
        return normal(x) < normal(y) ? x : y;
    return x < y ? x : y;
}

void solve() {
    int beg = 0;
    while(!cancalc(sa[beg])) beg++;
    int res = sa[beg++];
    while(beg < 4 * n + 1 && height[beg] >= n) {
        if(cancalc(sa[beg])) res = getbest(res, sa[beg]);
        beg++;
    }
    printf("%d %d\n", normal(res) + 1, res >= n);
}

void test() {
    int res = -1;
    for(int i = 0; i < 4 * n; ++i) if(cancalc(i)) {
        int t = ~res ? strncmp(s + i, s + res, n) : -1;
        if(t < 0) res = i;
        if(t == 0) res = getbest(res, i);
    }
    printf("%d %d\n", normal(res) + 1, res >= n);
}

void work() {
    scanf("%d", &T);
    while(T--) {
        scanf("%d%s", &n, a);
        for(int i = 0; i < n; ++i) a[i] = 'z' - a[i] + 'a';
        memcpy(a + n, a, n); a[2 * n] = 0;
        strcpy(s, a);
        reverse(a, a + 2 * n);
        strcpy(s + 2 * n, a); s[4 * n] = 0;
        makesa(4 * n + 1, 128);
        calheight(4 * n + 1);
        solve();
        //test();
    }
}

};

int main() {
    Oyk::work();
}
