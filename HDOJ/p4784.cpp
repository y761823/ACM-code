////////////////////System Comment////////////////////
////Welcome to Hangzhou Dianzi University Online Judge
////http://acm.hdu.edu.cn
//////////////////////////////////////////////////////
////Username: y761823
////Nickname: Oyk
////Run ID: 
////Submit time: 2014-09-12 18:39:52
////Compiler: GUN C++
//////////////////////////////////////////////////////
////Problem ID: 4784
////Problem Title: 
////Run result: Accept
////Run time:218MS
////Run memory:3352KB
//////////////////System Comment End//////////////////
#ifdef ONLINE_JUDGE
#define longformat "%lld"
#else
#define longformat "%I64d"
#endif // ONLINE_JUDGE

#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>
#include <queue>
using namespace std;
typedef long long LL;
#define FOR(i, st, ed) for(int i = st; i <= ed; ++i)

const int MAXN = 110;
const int MAXM = 210;
const int MAXB = 4 + 1;
const int MAXK = 5;
const int MAXT = 210;

struct Node {
    int u, b, k;
    Node() {}
    Node(int u, int b, int k):
        u(u), b(b), k(k) {}
};
int dis[MAXT][MAXN][MAXB][MAXK];
bool vis[MAXT][MAXN][MAXB][MAXK];
int price[MAXK][MAXN];
int n, m, B, K, R, T, Kase;

int head[MAXN], ecnt;
int to[MAXM], next[MAXM], cost_t[MAXM], cost_m[MAXM];

void init() {
    memset(head + 1, -1, n * sizeof(int));
    ecnt = 0;
}

void add_edge(int u, int v, int x, int y) {
    to[ecnt] = v; cost_t[ecnt] = x; cost_m[ecnt] = y; next[ecnt] = head[u]; head[u] = ecnt++;
}

queue<Node> que[MAXT];

bool judge(int x) {
    return x == 1 || x == n;
}

void push_back(int t, const Node &y, int val) {
    #define pos t][y.u][y.b][y.k
    if(judge(y.u) && y.k != 0) return ;
    if(t < 0 || val < 0 || dis[pos] >= val) return ;
    dis[pos] = val;
    if(!vis[pos] && y.u != n) {
        vis[pos] = true;
        que[t].push(y);
    }
    #undef pos
}

int solve() {
    FOR(t, 0, T) FOR(i, 1, n) FOR(b, 0, B) FOR(k, 0, K - 1) {
        dis[t][i][b][k] = -1;
        vis[t][i][b][k] = false;
    }
    push_back(T, Node(1, 0, 0), R);
    for(int t = T; t >= 0; --t) {
        while(!que[t].empty()) {
            Node x = que[t].front(); que[t].pop();
            int c = dis[t][x.u][x.b][x.k];

            for(int p = head[x.u]; ~p; p = next[p]) {
                int v = to[p], new_t = t - cost_t[p];
                if(c - cost_m[p] < 0) continue;
                push_back(new_t, Node(v, x.b, x.k), c - cost_m[p]);
                if(!judge(v) && x.b > 0) push_back(new_t, Node(v, x.b - 1, x.k), c - cost_m[p] + price[x.k][v]);
                if(!judge(v) && x.b < B) push_back(new_t, Node(v, x.b + 1, x.k), c - cost_m[p] - price[x.k][v]);
            }

            if(judge(x.u)) continue;
            int new_k = (x.k + 1) % K;
            push_back(t - 1, Node(x.u, x.b, new_k), c);
            if(x.b > 0) push_back(t - 1, Node(x.u, x.b - 1, new_k), c + price[new_k][x.u]);
            if(x.b < B) push_back(t - 1, Node(x.u, x.b + 1, new_k), c - price[new_k][x.u]);
        }
    }

    int res = -1;
    for(int t = 0; t <= T; ++t)
        res = max(res, dis[t][n][0][0]);
    return res;
}

int main() {
    scanf("%d", &Kase);
    FOR(kase, 1, Kase) {
        scanf("%d%d%d%d%d%d", &n, &m, &B, &K, &R, &T);
        init();
        FOR(i, 0, K - 1) FOR(j, 1, n) scanf("%d", &price[i][j]);
        for(int i = 0, u, v, x, y; i < m; ++i) {
            scanf("%d%d%d%d", &u, &v, &x, &y);
            add_edge(u, v, x, y);
        }
        int res = solve();
        printf("Case #%d: ", kase);
        if(res != -1) printf("%d\n", res);
        else puts("Forever Alone");
    }
}
