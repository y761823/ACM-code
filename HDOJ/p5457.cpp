#include <cstdio>
#include <iostream>
#include <algorithm>
#include <cstring>
#include <vector>
#include <queue>
using namespace std;
typedef long long LL;
#define FOR(i, s, t) for(int i = s; i <= t; ++i)

const int INF = 0x3f3f3f3f;

struct DINIC {
    static const int MAXV = 256 * 8 * 2 + 10;
    static const int MAXE = MAXV * 10;

    int head[MAXV], cur[MAXV], ecnt;
    int to[MAXE], nxt[MAXE], flow[MAXE];
    int n, st, ed;

    void init(int n) {
        this->n = n;
        memset(head + 1, -1, n * sizeof(int));
        ecnt = 0;
    }

    void add_edge(int u, int v, int f) {
        to[ecnt] = v; flow[ecnt] = f; nxt[ecnt] = head[u]; head[u] = ecnt++;
        to[ecnt] = u; flow[ecnt] = 0; nxt[ecnt] = head[v]; head[v] = ecnt++;
    }

    int dis[MAXV];

    bool bfs() {
        memset(dis + 1, 0x3f, n * sizeof(int));
        queue<int> que; que.push(st);
        dis[st] = 0;
        while(!que.empty()) {
            int u = que.front(); que.pop();
            for(int p = head[u]; ~p; p = nxt[p]) if(flow[p]) {
                int v = to[p];
                if(dis[u] + 1 < dis[v]) {
                    dis[v] = dis[u] + 1;
                    que.push(v);
                }
            }
        }
        return dis[ed] < INF;
    }

    int dfs(int u, int a) {
        if(u == ed || a == 0) return a;
        int outflow = 0, f;
        for(int &p = cur[u]; ~p; p = nxt[p]) {
            int v = to[p];
            if(dis[u] + 1 == dis[v] && (f = dfs(v, min(flow[p], a))) > 0) {
                flow[p] -= f;
                flow[p ^ 1] += f;
                a -= f;
                outflow += f;
                if(a == 0) break;
            }
        }
        return outflow;
    }

    int max_flow(int ss, int tt) {
        st = ss, ed = tt;
        int res = 0;
        while(bfs()) {
            memcpy(cur + 1, head + 1, n * sizeof(int));
            res += dfs(st, INF);
            if(res >= INF) return -1;
        }
        return res;
    }
} G;

struct Trie {
    struct Node {
        Node *go[2];
        int cost[2];
    } StatePool[256 * 8], *rt;
    int ncnt;

    Node* new_node() {
        Node* x = StatePool + ncnt++;
        x->go[0] = x->go[1] = 0;
        x->cost[0] = x->cost[1] = INF;
        return x;
    }

    int get_id(Node *x) {
        return x - StatePool + 1;
    }

    void init() {
        ncnt = 0;
        rt = new_node();
    }

    int insert(int v, const vector<int>& vec) {
        Node *p = rt;
        for(int i : vec) {
            int idx = (v >> i) & 1;
            if(!p->go[idx]) p->go[idx] = new_node();
            p = p->go[idx];
        }
        return get_id(p);
    }

    void modify(char str[], int n, int val) {
        Node *p = rt;
        for(int i = 0; i < n; ++i) {
            int idx = (str[i] == '1');
            if(!p->go[idx]) return ;
            if(i == n - 1) p->cost[idx] = min(p->cost[idx], val);
            p = p->go[idx];
        }
    }

    void dfs_build(Node *p, int offset) {
        int pid = get_id(p);
        for(int k = 0; k < 2; ++k) if(p->go[k]) {
            int sid = get_id(p->go[k]);
            if(offset == 0) G.add_edge(pid, sid, p->cost[k]);
            else G.add_edge(sid + offset, pid + offset, p->cost[k]);
            dfs_build(p->go[k], offset);
        }
    }
    void build(int offset) {
        dfs_build(rt, offset);
    }

} prefix, suffix;

const int MAXN = 510;

vector<int> prevec, sufvec;
char str[MAXN][10], op;
int a[MAXN], pid[MAXN], sid[MAXN], cost[MAXN];
int n, m, T;

int solve() {
    G.init(prefix.ncnt + suffix.ncnt);
    prefix.build(0);
    suffix.build(prefix.ncnt);
    for(int i = 0; i < n; ++i)
        G.add_edge(pid[i], sid[i] + prefix.ncnt, INF);
    return G.max_flow(prefix.get_id(prefix.rt), suffix.get_id(suffix.rt) + prefix.ncnt);
}

int main() {
    for(int i = 0; i < 8; ++i) {
        prevec.push_back(7 - i);
        sufvec.push_back(i);
    }

    scanf("%d", &T);
    for(int t = 1; t <= T; ++t) {
        scanf("%d%d", &n, &m);

        for(int i = 0; i < n; ++i)
            scanf("%d", &a[i]);
        sort(a, a + n);
        n = unique(a, a + n) - a;

        prefix.init(); suffix.init();
        for(int i = 0; i < n; ++i) {
            pid[i] = prefix.insert(a[i], prevec);
            sid[i] = suffix.insert(a[i], sufvec);
        }

        for(int i = 0; i < m; ++i) {
            scanf(" %c%s%d", &op, str[i], &cost[i]);
            if(op == 'P') prefix.modify(str[i], strlen(str[i]), cost[i]);
            if(op == 'S') {
                reverse(str[i], str[i] + strlen(str[i]));
                suffix.modify(str[i], strlen(str[i]), cost[i]);
            }
        }

        printf("Case #%d: %d\n", t, solve());
    }
}
