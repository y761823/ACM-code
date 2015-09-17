#include <cstdio>
#include <algorithm>
#include <iostream>
#include <cstring>
#include <vector>
using namespace std;
typedef long long LL;

const int MAXN = 200010;
const int INF = 0x3f3f3f3f;

int s[MAXN], p[MAXN];
int n, m, T;

void manachar(int s[], int n) {
    int mx = 0, id;
    for(int i = 1; i < n; ++i) {
        if(mx > i) p[i] = min(p[2 * id - i], mx - i);
        else p[i] = 1;
        while(s[i + p[i]] == s[i - p[i]]) ++p[i];
        if(i + p[i] > mx) {
            id = i;
            mx = i + p[i];
        }
    }
}

int root(int l, int r) { return (l + r) | (l != r); }
#define x root(l, r)
#define mid ((l + r) >> 1)
#define ll root(l, mid)
#define rr root(mid + 1, r)

int mint[MAXN];

void insert(int l, int r, int pos, int val) {
    if(l == r) {
        mint[x] = val;
    } else {
        if(pos <= mid) insert(l, mid, pos, val);
        if(mid < pos) insert(mid + 1, r, pos, val);
        mint[x] = min(mint[ll], mint[rr]);
    }
}

int query(int l, int r, int a, int b) {
    if(a <= l && r <= b) {
        return mint[x];
    } else {
        int res = INF;
        if(a <= mid) res = min(res, query(l, mid, a, b));
        if(mid < b) res = min(res, query(mid + 1, r, a, b));
        return res;
    }
}

vector<int> clist[MAXN];

int solve() {
    int res = 0;
    for(int i = 1; i <= n; ++i) {
        int len = p[i * 2 + 1] / 2;
        if(len > 0) {
            if(i > 1) res = max(res, i - query(1, n, max(i - len, 1), i - 1));
            insert(1, n, i, i);
            clist[min(i + len, n)].push_back(i);
        }
        for(int pos : clist[i])
            insert(1, n, pos, INF);
        clist[i].clear();
    }
    return res * 3;
}

int main() {
    memset(mint, 0x3f, sizeof(mint));
    //freopen("H:/in.txt", "r", stdin);
    scanf("%d", &T);
    for(int t = 1; t <= T; ++t) {
        scanf("%d", &n);
        m = 0;
        s[m++] = INF; s[m++] = -1;
        for(int i = 0; i < n; ++i) {
            scanf("%d", &s[m++]);
            s[m++] = -1;
        }
        s[m] = INF - 1;
        manachar(s, m);
        printf("Case #%d: %d\n", t, solve());
    }
}
