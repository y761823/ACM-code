////////////////////System Comment////////////////////
////Welcome to Hangzhou Dianzi University Online Judge
////http://acm.hdu.edu.cn
//////////////////////////////////////////////////////
////Username: y761823
////Nickname: Oyk
////Run ID: 
////Submit time: 2014-08-05 00:02:22
////Compiler: GUN C++
//////////////////////////////////////////////////////
////Problem ID: 4898
////Problem Title: 
////Run result: Accept
////Run time:2531MS
////Run memory:9276KB
//////////////////System Comment End//////////////////
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;
typedef long long LL;

const int MAXN = 2010;

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

void init(int n = 2000) {
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
            best[i][j] = min(best[i - 1][j], best[i - 1][j + (1 << (i - 1))]);
    }
}

int lcp(int a, int b) {
    if(a == b) return n;
    a = rank[a], b = rank[b];
    if(a > b) swap(a, b);
    ++a;
    int t = logn[b - a + 1];
    return min(best[t][a], best[t][b - (1 << t) + 1]);
}

int cmp(int x, int n, int y, int m) {
    int t = lcp(x, y);
    if(n > t && m > t) return s[x + t] - s[y + t];
    return n - m;
}

struct Node {
    int pos, len;
    Node() {}
    Node(int pos, int len): pos(pos), len(len) {}
    bool operator < (const Node &rhs) const {
        return cmp(pos, len, rhs.pos, rhs.len) < 0;
    }
    void print() {
        for(int i = pos; i < pos + len; ++i)
            putchar(s[i]);
        puts("");
    }
};

const int MAXV = MAXN >> 1;
Node src[MAXV * MAXV];
bool mat[MAXV][MAXV], ban[MAXV];
int go[MAXV], cnt[MAXV];

bool check(Node p) {
    memset(mat, 0, sizeof(mat));
    memset(ban, 0, sizeof(ban));
    for(int i = 0; i < n; ++i) {
        go[i] = n;
        if(cmp(i, n, p.pos, p.len) >= 0) go[i] = min(go[i], min(p.len, lcp(p.pos % n, i)));
        cnt[i] = go[i];
        for(int j = i + 1; j <= i + go[i]; ++j)
            mat[j % n][i] = true;
    }
    for(int _ = 0; _ < n; ++_) {
        bool flag = false;
        for(int i = 0; i < n; ++i) if(!ban[i] && !cnt[i]) {
            ban[i] = flag = true;
            for(int j = 0; j < n; ++j) cnt[j] -= mat[i][j];
        }
        if(!flag) break;
    }
    int c = 0;
    for(int i = 0; i < n; ++i) if(cnt[i]) cnt[c++] = cnt[i];
    for(int st = 0; st < c; ++st) {
        int x = st, y = 0;
        while(x < st + c) x += cnt[x % c], ++y;
        if(c >= k && y <= k) return true;
    }
    return false;
}

void solve() {
    int c = 0;
    for(int i = 0; i < n; ++i)
        for(int j = 1; j <= n; ++j) src[c++] = Node(i, j);
    sort(src, src + c);
    //c = unique(src, src + c) - src;
    int l = 0, r = c;
    while(l < r) {
        int mid = (l + r) >> 1;
        //src[mid].print();
        if(!check(src[mid])) l = mid + 1;
        else r = mid;
    }
    src[l].print();
}

int main() {
    scanf("%d", &T);
    while(T--) {
        scanf("%d%d", &n, &k);
        scanf("%s", s);
        memcpy(s + n, s, n * sizeof(char));
        s[n << 1] = 0;
        makesa(2 * n + 1, 128);
        calheight(2 * n);
        initRMQ(2 * n);
        solve();
    }
}
