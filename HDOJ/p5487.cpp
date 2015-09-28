#include <cstdio>
#include <iostream>
#include <algorithm>
#include <cstring>
#include <tuple>
#include <queue>
using namespace std;
typedef long long LL;
#define FOR(i, s, t) for(int i = s; i <= t; ++i)

const int MAXN = 1010;
const int SIGMA = 26;

struct DFA {
    int go[MAXN][SIGMA];
    bool isend[MAXN];
    int n, m, k;

    void init() {
        memset(isend, 0, (n + 1) * sizeof(bool));
        memset(go, 0, (n + 1) * sizeof(go[0]));
    }

    void read() {
        scanf("%d%d%d", &n, &m, &k);
        init();
        for(int i = 0, x; i < k; ++i) {
            scanf("%d", &x);
            isend[x + 1] = true;
        }
        char c;
        for(int i = 0, u, v; i < m; ++i) {
            scanf("%d%d %c", &u, &v, &c);
            go[u + 1][c - 'a'] = v + 1;
        }
    }
} a, b;

typedef tuple<int, int, int> Msg;
#define getx(t) get<0>(t)
#define gety(t) get<1>(t)
#define getg(t) get<2>(t)

Msg pre[MAXN][MAXN];
bool vis[MAXN][MAXN];
int T;

void print(int x, int y) {
    if(x != 1 || y != 1) {
        print(getx(pre[x][y]), gety(pre[x][y]));
        putchar(getg(pre[x][y]) + 'a');
    }
}

void solve() {
    queue<int> que; que.push(1); que.push(1);
    for(int i = 0; i <= a.n; ++i)
        memset(vis[i], 0, (b.n + 1) * sizeof(bool));
    vis[1][1] = true;
    while(!que.empty()) {
        int x = que.front(); que.pop();
        int y = que.front(); que.pop();
        if(a.isend[x] ^ b.isend[y]) {
            print(x, y);
            puts("");
            return ;
        }
        for(int i = 0; i < SIGMA; ++i) {
            int newx = a.go[x][i], newy = b.go[y][i];
            if(!vis[newx][newy]) {
                vis[newx][newy] = true;
                pre[newx][newy] = Msg(x, y, i);
                que.push(newx); que.push(newy);
            }
        }
    }
    puts("0");
}

int main() {
    scanf("%d", &T);
    for(int t = 1; t <= T; ++t) {
        a.read(); b.read();
        printf("Case #%d: ", t);
        solve();
    }
}
