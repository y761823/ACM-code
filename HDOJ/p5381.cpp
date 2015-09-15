#include <cstdio>
#include <algorithm>
#include <iostream>
#include <cstring>
#include <vector>
using namespace std;
typedef long long LL;

const int MAXN = 10010;
const int SQRT = 100;
const int INF = 0x3f3f3f3f;

vector<pair<int, int> > lgcd[MAXN], rgcd[MAXN]; /// cnt, value
int a[MAXN];
int n, q, T;

void init_reg() {
    for(int i = 1; i <= n; ++i) {
        rgcd[i].push_back(make_pair(1, a[i]));
        for(auto p : rgcd[i - 1]) {
            int gcd = __gcd(p.second, a[i]);
            if(gcd == rgcd[i].back().second) rgcd[i].back().first += p.first;
            else rgcd[i].push_back(make_pair(p.first, gcd));
        }
    }
    lgcd[n + 1].clear();
    for(int i = n; i > 0; --i) {
        lgcd[i].push_back(make_pair(1, a[i]));
        for(auto p : lgcd[i + 1]) {
            int gcd = __gcd(p.second, a[i]);
            if(gcd == lgcd[i].back().second) lgcd[i].back().first += p.first;
            else lgcd[i].push_back(make_pair(p.first, gcd));
        }
    }
}

struct Query {
    int l, r, id;
    void read(int i) {
        id = i;
        scanf("%d%d", &l, &r);
    }
    bool operator < (const Query &rhs) const {
        if(l / SQRT != rhs.l / SQRT) return l < rhs.l;
        return r < rhs.r;
    }
} query[MAXN];
LL ans[MAXN];

LL calc_left(int l, int r) {
    int cnt = r - l + 1;
    LL res = 0;
    for(auto p : lgcd[l]) {
        res += (LL)min(cnt, p.first) * p.second;
        cnt -= p.first;
        if(cnt <= 0) break;
    }
    return res;
}

LL calc_right(int l, int r) {
    int cnt = r - l + 1;
    LL res = 0;
    for(auto p : rgcd[r]) {
        res += (LL)min(cnt, p.first) * p.second;
        cnt -= p.first;
        if(cnt <= 0) break;
    }
    return res;
}

void solve() {
    LL res = 0;
    for(int v = 0, l = 0, r = 0; v < q; ++v) {
        while(query[v].l < l) res += calc_left(--l, r);
        while(r < query[v].r) res += calc_right(l, ++r);
        while(l < query[v].l) res -= calc_left(l++, r);
        while(query[v].r < r) res -= calc_right(l, r--);
        ans[query[v].id] = res;
    }
    for(int i = 0; i < q; ++i)
        printf("%I64d\n", ans[i]);
}

int main() {
    scanf("%d", &T);
    while(T--) {
        scanf("%d", &n);
        for(int i = 1; i <= n; ++i) {
            scanf("%d", &a[i]);
            lgcd[i].clear();
            rgcd[i].clear();
        }
        init_reg();
        scanf("%d", &q);
        for(int i = 0; i < q; ++i)
            query[i].read(i);
        sort(query, query + q);
        solve();
    }
}
