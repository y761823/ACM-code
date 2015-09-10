#include <cstdio>
#include <algorithm>
#include <iostream>
#include <cstring>
#include <vector>
#include <map>
using namespace std;
typedef long long LL;
#define REP(i, n) for(int i = 0; i < n; ++i)

const int MAXN = 66;
const int MOD = 1e9 + 7;
const int INF = 0x3f3f3f3f;

int a[MAXN], b[MAXN], l[MAXN], ans[MAXN];
LL cnt[MAXN], c[MAXN], d[MAXN];
map<LL, int> sumdis[MAXN];
map<pair<LL, LL>, int> dis[MAXN];
int n;

int find_dis(int id, LL u, LL v) {
    if(u > v) swap(u, v);
    if(dis[id].find(make_pair(u, v)) != dis[id].end())
       return dis[id][make_pair(u, v)];
    LL res = 0, acnt = cnt[a[id]];
    bool uina = (u < acnt), vina = (v < acnt);
    if(uina && vina) res = find_dis(a[id], u, v);
    else if(!uina && !vina) res = find_dis(b[id], u - acnt, v - acnt);
    else res = find_dis(a[id], u, c[id]) + (LL)l[id] + find_dis(b[id], v - acnt, d[id]);
    return dis[id][make_pair(u, v)] = res % MOD;
}

int find_sumdis(int id, LL u) {
    if(sumdis[id].find(u) != sumdis[id].end())
        return sumdis[id][u];
    LL res = 0, acnt = cnt[a[id]];
    if(u < acnt) {
        res = find_sumdis(a[id], u) + find_sumdis(b[id], d[id]);
        res += (cnt[b[id]] % MOD) * (find_dis(a[id], u, c[id]) + l[id]);
    } else {
        res = find_sumdis(b[id], u - acnt) + find_sumdis(a[id], c[id]);
        res += (cnt[a[id]] % MOD) * (find_dis(b[id], u - acnt, d[id]) + l[id]);
    }
    return sumdis[id][u] = res % MOD;
}

int main() {
    sumdis[0][0] = 0;
    dis[0][make_pair(0, 0)] = 0;
    cnt[0] = 1;
    ans[0] = 0;

    while(scanf("%d", &n) != EOF) {
        for(int i = 1; i <= n; ++i) {
            scanf("%d%d%I64d%I64d%d", &a[i], &b[i], &c[i], &d[i], &l[i]);
            sumdis[i].clear();
            dis[i].clear();
        }
        for(int id = 1; id <= n; ++id) {
            LL res = ans[a[id]] + ans[b[id]];
            res += (cnt[b[id]] % MOD) * find_sumdis(a[id], c[id]);
            res += (cnt[a[id]] % MOD) * find_sumdis(b[id], d[id]);
            res += (cnt[a[id]] % MOD) * (cnt[b[id]] % MOD) % MOD * l[id];
            cnt[id] = cnt[a[id]] + cnt[b[id]];
            printf("%d\n", ans[id] = res % MOD);
        }
    }
}
