#include <cstdio>
#include <algorithm>
#include <iostream>
#include <cstring>
#include <queue>
using namespace std;
typedef long long LL;

const int MAXV = 200010;
const int INF = 0x3f3f3f3f;

struct Candy {
    int cnt, cost;
} que[MAXV];
int a[MAXV], buy[MAXV], sell[MAXV];
int T, n, C;

void change_sell(int &l, int &r, int val) {
    if(l < r && que[l].cost <= val) {
        int cnt = 0;
        while(l < r && que[l].cost <= val)
            cnt += que[l++].cnt;
        que[--l] = {cnt, val};
    }
}

void sell_expensive(int &l, int &r, int &own, LL &res, int val) {
    while(l < r && que[r - 1].cost >= val) {
        res += (LL)que[r - 1].cnt * que[r - 1].cost;
        own -= que[r - 1].cnt;
        r--;
    }
}

LL solve() {
    LL res = 0;
    int l = 0, r = 0, own = 0;
    for(int i = 0; i < n; ++i) {
        change_sell(l, r, sell[i]);
        sell_expensive(l, r, own, res, buy[i]);

        que[r++] = {C - own, buy[i]};
        res -= LL(C - own) * buy[i];

        int cost = a[i + 1] - a[i];
        own = C - cost;
        while(cost > 0) {
            int t = min(que[l].cnt, cost);
            cost -= t; que[l].cnt -= t;
            if(que[l].cnt == 0) l++;
        }
    }
    change_sell(l, r, sell[n]);
    sell_expensive(l, r, own, res, 0);
    return -res;
}

int main() {
    scanf("%d", &T);
    while(T--) {
        scanf("%d%d", &n, &C);
        for(int i = 1; i <= n; ++i) scanf("%d", &a[i]);
        for(int i = 0; i <= n; ++i) scanf("%d%d", &buy[i], &sell[i]);
        printf("%I64d\n", solve());
    }
}
