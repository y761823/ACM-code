#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>

typedef long long LL;

const int MAXN = 100010;
const int INF = 0x3f3f3f3f;

char s[MAXN];
int sa[MAXN], rank[MAXN], c[MAXN], tmp[MAXN], height[MAXN];
int n, k, T;

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
        k -= (k > 0);
        int j = sa[rank[i] - 1];
        while(s[i + k] == s[j + k]) ++k;
    }
}

int logn[MAXN];
int best[20][MAXN];

void init(int n = 100000) {
    static bool done = false;
    if(done) return ;
    logn[0] = -1;
    for(int i = 1; i <= n; ++i)
        logn[i] = logn[i - 1] + ((i & (i - 1)) == 0);
    done = true;
}

void initRMQ(int n) {
    init();
    for(int i = 1; i <= n; ++i) best[0][i] = height[i];
    for(int i = 1; i <= logn[n]; ++i) {
        int ed = n - (1 << i) + 1;
        for(int j = 1; j <= ed; ++j)
            best[i][j] = std::min(best[i - 1][j], best[i - 1][j + (1 << (i - 1))]);
    }
}

int lcp(int a, int b) {
    if(a == b) return n;
    a = rank[a], b = rank[b];
    if(a > b) std::swap(a, b);
    ++a;
    int t = logn[b - a + 1];
    return std::min(best[t][a], best[t][b - (1 << t) + 1]);
}

int root(int l, int r) { return (l + r) | (l != r); }
#define x root(l, r)
#define mid ((l + r) >> 1)
#define ll root(l, mid)
#define rr root(mid + 1, r)
int mint[MAXN << 1];

void build(int l, int r) {
    if(l == r) {
        mint[x] = sa[l];
    } else {
        build(l, mid);
        build(mid + 1, r);
        mint[x] = std::min(mint[ll], mint[rr]);
    }
}

int _query(int l, int r, int pos, int limit) {
    if(mint[x] >= pos) return INF;
    int llcp = lcp(sa[l], pos), rlcp = lcp(sa[r], pos);
    if(llcp < limit && rlcp < limit) return INF;
    if(llcp >= limit && rlcp >= limit) {
        return mint[x];
    } else {
        return std::min(_query(l, mid, pos, limit), _query(mid + 1, r, pos, limit));
    }
}
int query(int l, int r, int pos, int limit) {
    if(l > r || mint[x] >= pos) return INF;
    if(l <= rank[pos] && rank[pos] <= r) {
        int llcp = lcp(sa[l], pos), rlcp = lcp(sa[r], pos);
        if(llcp >= limit && rlcp >= limit) return mint[x];
        return std::min(query(l, mid, pos, limit), query(mid + 1, r, pos, limit));
    } else {
        return _query(l, r, pos, limit);
    }
}

int query(int pos, int limit) {
    return query(1, n, pos, limit);
}

void solve() {
    int pos = 0;
    while(pos < n) {
        int add = 0, tmp = -1, res = -1;
        while(pos + add < n && (tmp = query(pos, add + 1)) < pos) {
            add++;
            res = tmp;
        }
        if(add) {
            printf("%d %d\n", add, res);
            pos += add;
        } else {
            printf("-1 %d\n", s[pos++]);
        }
    }
}

int main() {
    scanf("%d", &T);
    for(int t = 1; t <= T; ++t) {
        scanf("%s", s);
        n = strlen(s);
        makesa(n + 1, 128);
        calheight(n);
        initRMQ(n);
        build(1, n);

        printf("Case #%d:\n", t);
        solve();
    }
}
