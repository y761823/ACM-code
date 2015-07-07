////////////////////System Comment////////////////////
////Welcome to Hangzhou Dianzi University Online Judge
////http://acm.hdu.edu.cn
//////////////////////////////////////////////////////
////Username: y761823
////Nickname: Oyk
////Run ID: 
////Submit time: 2014-03-16 20:56:41
////Compiler: GUN C++
//////////////////////////////////////////////////////
////Problem ID: 1569
////Problem Title: 
////Run result: Accept
////Run time:0MS
////Run memory:504KB
//////////////////System Comment End//////////////////
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <queue>
using namespace std;

const int MAXN = 3000;
const int MAXE = 30010;
const int INF = 0x3fff3fff;

struct SAP {
    int head[MAXN], dis[MAXN], pre[MAXN], cur[MAXN], gap[MAXN];
    int to[MAXE], next[MAXE], flow[MAXE];
    int n, st, ed, ecnt;

    void init() {
        memset(head, 0, sizeof(head));
        ecnt = 2;
    }

    void add_edge(int u, int v, int c) {
        to[ecnt] = v; flow[ecnt] = c; next[ecnt] = head[u]; head[u] = ecnt++;
        to[ecnt] = u; flow[ecnt] = 0; next[ecnt] = head[v]; head[v] = ecnt++;
        //printf("%d->%d flow = %d\n", u, v, c);
    }

    void bfs() {
        memset(dis, 0x3f, sizeof(dis));
        queue<int> que; que.push(ed);
        dis[ed] = 0;
        while(!que.empty()) {
            int u = que.front(); que.pop();
            ++gap[dis[u]];
            for(int p = head[u]; p; p = next[p]) {
                int &v = to[p];
                if(flow[p ^ 1] && dis[v] > n) {
                    dis[v] = dis[u] + 1;
                    que.push(v);
                }
            }
        }
    }

    int Max_flow(int ss, int tt, int nn) {
        st = ss; ed = tt; n = nn;
        int ans = 0, minFlow = INF, u;
        for(int i = 0; i <= n; ++i) {
            cur[i] = head[i];
            gap[i] = 0;
        }
        u = pre[st] = st;
        bfs();
        while(dis[st] < n) {
            bool flag = false;
            for(int &p = cur[u]; p; p = next[p]) {
                int &v = to[p];
                if(flow[p] && dis[u] == dis[v] + 1) {
                    flag = true;
                    minFlow = min(minFlow, flow[p]);
                    pre[v] = u;
                    u = v;
                    if(u == ed) {
                        ans += minFlow;
                        while(u != st) {
                            u = pre[u];
                            flow[cur[u]] -= minFlow;
                            flow[cur[u] ^ 1] += minFlow;
                        }
                        minFlow = INF;
                    }
                    break;
                }
            }
            if(flag) continue;
            int minDis = n - 1;
            for(int p = head[u]; p; p = next[p]) {
                int &v = to[p];
                if(flow[p] && minDis > dis[v]) {
                    minDis = dis[v];
                    cur[u] = p;
                }
            }
            if(--gap[dis[u]] == 0) break;
            gap[dis[u] = minDis + 1]++;
            u = pre[u];
        }
        return ans;
    }
} G;

int n, m;
int mat[55][55];

int main() {
    while(scanf("%d%d", &n, &m) != EOF) {
        for(int i = 1; i <= n; ++i)
            for(int j = 1; j <= m; ++j) scanf("%d", &mat[i][j]);
        G.init();
        int ss = n * m + 1, tt = n * m + 2;
        int cnt = 0, sum = 0;
        for(int i = 1; i <= n; ++i) {
            for(int j = 1; j <= m; ++j) {
                ++cnt; sum += mat[i][j];
                if((i + j) & 1) {
                    G.add_edge(ss, cnt, mat[i][j]);
                    if(j != 1) G.add_edge(cnt, cnt - 1, INF);
                    if(i != 1) G.add_edge(cnt, cnt - m, INF);
                    if(j != m) G.add_edge(cnt, cnt + 1, INF);
                    if(i != n) G.add_edge(cnt, cnt + m, INF);
                }
                else G.add_edge(cnt, tt, mat[i][j]);
            }
        }
        printf("%d\n", sum - G.Max_flow(ss, tt, tt));
    }
}