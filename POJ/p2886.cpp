#include <cstdio>
#include <algorithm>
#include <cstring>
#include <iostream>
using namespace std;
typedef long long LL;

const int MAXN = 500010;
const int MAXT = 1000010;
const int INF = 0x3f3f3f3f;

char name[MAXN][12];
int val[MAXN], weight[MAXN];
int sum[MAXT];
int n, k;

void init(int n = 500000) {
    for(int i = 1; i <= n; ++i) {
        for(int j = i; j <= n; j += i)
            weight[j]++;
    }
}

int find_max(int n) {
    int res = 1;
    for(int i = 2; i <= n; ++i)
        if(weight[i] > weight[res]) res = i;
    return res;
}

int id(int l, int r) {
    return (l + r) | (l != r);
}
#define x id(l, r)
#define mid ((l + r) >> 1)
#define ll id(l, mid)
#define rr id(mid + 1, r)

void update(int l, int r) {
    sum[x] = sum[ll] + sum[rr];
}

void build(int l, int r) {
    if(l == r) {
        sum[x] = 1;
    } else {
        build(l, mid);
        build(mid + 1, r);
        update(l, r);
    }
}

int query(int l, int r, int kth) {
    if(l == r) {
        sum[x]--;
        return l;
    } else {
        int res;
        if(sum[ll] >= kth) res = query(l, mid, kth);
        else res = query(mid + 1, r, kth - sum[ll]);
        update(l, r);
        return res;
    }
}

void solve(int cnt) {
    int now = query(0, n - 1, k--), root = id(0, n - 1);
    for(int i = 1; i < cnt; ++i) {
        k = ((k - (val[now] > 0) + val[now]) % sum[root] + sum[root]) % sum[root];
        now = query(0, n - 1, k + 1);
    }
    printf("%s %d\n", name[now], weight[cnt]);
}

int main() {
    init();
    while(scanf("%d%d", &n, &k) != EOF) {
        for(int i = 0; i < n; ++i)
            scanf("%s%d", name[i], &val[i]);
        build(0, n - 1);
        solve(find_max(n));
    }
}
