#include <cstdio>
#include <cstring>
#include <queue>
using namespace std;

const int MAXN = 210;
const int MAXE = 40010 * 2;
const int INF = 0x7f7f7f7f;

struct Dinic {
    int n, m, st, ed, ecnt, maxlen;
    int head[MAXN];
    int cur[MAXN], d[MAXN];
    int to[MAXE], next[MAXE], flow[MAXE], cap[MAXE], len[MAXE];

    void init(int ss, int tt) {
        st = ss; ed = tt;
        ecnt = 2;
        memset(head, 0, sizeof(head));
    }

    void add_edge(int u, int v, int c, int l) {
        len[ecnt] = l; to[ecnt] = v; cap[ecnt] = c; flow[ecnt] = 0; next[ecnt] = head[u]; head[u] = ecnt++;
        len[ecnt] = l; to[ecnt] = u; cap[ecnt] = c; flow[ecnt] = 0; next[ecnt] = head[v]; head[v] = ecnt++;
    }

    bool bfs() {
        memset(d, 0, sizeof(d));
        queue<int> que; que.push(st);
        d[st] = 1;
        while(!que.empty()) {
            int u = que.front(); que.pop();
            for(int p = head[u]; p; p = next[p]) {
                if(len[p] > maxlen) continue;
                int v = to[p];
                if(!d[v] && cap[p] > flow[p]) {
                    d[v] = d[u] + 1;
                    que.push(v);
                    if(v == ed) return true;
                }
            }
        }
        return d[ed];
    }

    int dfs(int u, int a) {
        if(u == ed || a == 0) return a;
        int outflow = 0, f;
        for(int &p = cur[u]; p; p = next[p]) {
            if(len[p] > maxlen) continue;
            int v = to[p];
            if(d[u] + 1 == d[v] && (f = dfs(v, min(a, cap[p] - flow[p]))) > 0) {
                flow[p] += f;
                flow[p ^ 1] -= f;
                outflow += f;
                a -= f;
                if(a == 0) break;
            }
        }
        return outflow;
    }

    int Maxflow(int mlen) {
        int ans = 0; maxlen = mlen;
        while(bfs()) {
            for(int i = 0; i <= ed; ++i) cur[i] = head[i];
            ans += dfs(st, INF);
        }
        return ans;
    }
} G;

int main() {
    int n, m, T, left = 0, right = 0;
    scanf("%d%d%d", &n, &m, &T);
    G.init(1, n);
    for(int i = 0; i < m; ++i) {
        int a, b, c;
        scanf("%d%d%d", &a, &b, &c);
        G.add_edge(a, b, 1, c);
        if(right < c) right = c;
    }
    while(left < right) {
        memset(G.flow, 0, sizeof(G.flow));
        int mid = (left + right) >> 1;
        if(G.Maxflow(mid) < T) left = mid + 1;
        else right = mid;
    }
    printf("%d\n", right);
}
