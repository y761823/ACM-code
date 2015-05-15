#include <cstdio>
#include <algorithm>
#include <cstring>
#include <iostream>
#include <set>
using namespace std;
typedef long long LL;

const int MOD = 2000007;

struct HashMap {
    int head[MOD], ecnt;
    LL to[MOD];
    int cost[MOD], next[MOD];

    void clear() {
        memset(head, -1, sizeof(head));
        ecnt = 0;
    }

    void insert(LL val, int c) {
        int h = val % MOD;
        for(int p = head[h]; ~p; p = next[p])
            if(to[p] == val) return ;
        to[ecnt] = val; cost[ecnt] = c; next[ecnt] = head[h]; head[h] = ecnt++;
    }
};

HashMap zz;
int T, n, mo, c;

void dfs(int n, int st, LL ans) {
    if(n == 0) {
        zz.insert(ans, c);
        return ;
    }
    for(int i = st; i <= n; ++i)
        if(i != 4) dfs(n - i, i, ans * i);
}

int main() {
    zz.clear();
    zz.insert(1, 1);
    for(c = 2; c <= 70; ++c) dfs(c, 2, 1);

    scanf("%d", &T);
    while(T--) {
        scanf("%d%d", &n, &mo);
        set<int> st;
        for(int i = 0; i < zz.ecnt; ++i) if(zz.cost[i] <= n)
            st.insert(zz.to[i] % mo);
        printf("%d\n", st.size());
    }
}