#include <cstdio>
#include <algorithm>
#include <iostream>
#include <cstring>
#include <queue>
using namespace std;
typedef long long LL;
#define REP(i, n) for(int i = 0; i < n; ++i)

const int MAXN = 150010;

struct Open {
    int t, p;
    bool operator < (const Open &rhs) const {
        return t < rhs.t;
    }
} door[MAXN];

char name[MAXN][201];
int gift[MAXN], query[MAXN], ans[MAXN];
int n, m, q, T;

void solve() {
    priority_queue<pair<int, int> > que;
    int acnt = 0;
    for(int i = 0, now = 0; i < m; ++i) {
        while(now < door[i].t && now < n)
            que.push(make_pair(gift[now], -now)), now++;
        for(int _ = 0; _ < door[i].p && !que.empty(); ++_)
            ans[acnt++] = -que.top().second, que.pop();
        if(door[i].t == n) break;
    }
    bool flag = false;
    for(int i = 0; i < q; ++i) {
        if(flag) printf(" ");
        else flag = true;
        printf("%s", name[ans[query[i] - 1]]);
    }
    puts("");
}

int main() {
    scanf("%d", &T);
    while(T--) {
        scanf("%d%d%d", &n, &m, &q);
        for(int i = 0; i < n; ++i)
            scanf("%s%d", name[i], &gift[i]);
        for(int i = 0; i < m; ++i)
            scanf("%d%d", &door[i].t, &door[i].p);
        door[m].t = door[m].p = n; m++;
        sort(door, door + m);
        for(int i = 0; i < q; ++i)
            scanf("%d", &query[i]);
        solve();
    }
}
