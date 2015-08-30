#include <cstdio>
#include <algorithm>
#include <cstring>
#include <iostream>
#include <queue>
#include <string>
using namespace std;
typedef long long LL;

const int MAXN = 22;
const int INF = 0x3f3f3f3f;

struct Node {
    string s;
    int dis, r, c;
    void init() {
        s.clear();
        dis = INF;
    }
    bool operator < (const Node &rhs) const {
        if(dis != rhs.dis) return dis < rhs.dis;
        return s < rhs.s;
    }
    bool operator != (const Node &rhs) const {
        return dis != rhs.dis || s != rhs.s;
    }
    Node add(char c) const {
        Node res; res.init();
        if(dis == INF) return res;
        res.s = s + c;
        res.dis = res.s.length();
        return res;
    }
    Node operator + (const Node &rhs) const {
        Node res; res.init();
        if(dis == INF || rhs.dis == INF) return res;
        res.s = s + rhs.s;
        res.dis = res.s.length();
        return res;
    }
};

char mat[MAXN][MAXN];
int id[MAXN][MAXN];
Node dis[MAXN][MAXN], tdis[MAXN][MAXN];
int n, m;

int rr[MAXN], cc[MAXN], sr, sc;;
int ww;

void findAllStar() {
    ww = 0;
    for(int i = 0; i < n; ++i) {
        for(int j = 0; j < m; ++j) {
            if(mat[i][j] == '*') {
                rr[ww] = i;
                cc[ww] = j;
                id[i][j] = ww++;
            }
        }
    }
    for(int i = 0; i < n; ++i) {
        for(int j = 0; j < m; ++j) {
            if(mat[i][j] == 'S') {
                rr[ww] = i;
                cc[ww] = j;
                id[i][j] = ww;
            }
        }
    }
}

int fx[] = {0, 1, 0, -1};
int fy[] = {1, 0, -1, 0};
char fc[] = "ESWN";

void bfs(int r, int c, Node nowdis[]) {
    for(int i = 0; i <= ww; ++i) nowdis[i].init();
    for(int i = 0; i < n; ++i)
        for(int j = 0; j < m; ++j) tdis[i][j].init();
    tdis[r][c].dis = 0;
    tdis[r][c].r = r;
    tdis[r][c].c = c;
    priority_queue<Node> que; que.push(tdis[r][c]);
    while(!que.empty()) {
        Node t = que.top(); que.pop();
        if(t != tdis[t.r][t.c]) continue;

        if(strchr("*S", mat[t.r][t.c]))
            nowdis[id[t.r][t.c]] = t;

        for(int f = 0; f < 4; ++f) {
            Node v = t.add(fc[f]);
            v.r = t.r + fx[f];
            v.c = t.c + fy[f];
            if(strchr("#X", mat[v.r][v.c])) continue;
            if(v < tdis[v.r][v.c]) {
                tdis[v.r][v.c] = v;
                que.push(v);
            }
        }
    }
}

Node dp[MAXN][1 << 12];
bool vis[MAXN][1 << 12];

void solve() {
    for(int i = 0; i < ww; ++i)
        for(int j = 0; j < (1 << ww); ++j) dp[i][j].init(), vis[i][j] = false;
    queue<pair<int, int> > que;
    for(int i = 0; i < ww; ++i) {
        dp[i][1 << i] = dis[ww][i];
        que.push(make_pair(i, 1 << i));
        vis[i][1 << i] = true;
    }
    while(!que.empty()) {
        int last = que.front().first, state = que.front().second; que.pop();
        for(int i = 0; i < ww; ++i) {
            int newState = state | (1 << i);
            if(newState == state) continue;

            Node newdis = dp[last][state] + dis[last][i];
            if(newdis < dp[i][newState]) {
                dp[i][newState] = newdis;
                if(!vis[i][newState]) {
                    vis[i][newState] = true;
                    que.push(make_pair(i, newState));
                }
            }
        }
    }
}

void print() {
    Node res; res.init();
    int cnt = 0;
    for(int i = 0; i < ww; ++i) if(dis[i][ww].dis < INF) {
        for(int j = 0; j < (1 << ww); ++j) if((1 << i) & j) {
            if(dp[i][j].dis == INF) continue;
            int t = __builtin_popcount(j);
            if(t > cnt) {
                res = dp[i][j] + dis[i][ww];
                cnt = t;
            } else if(t == cnt) {
                res = min(res, dp[i][j] + dis[i][ww]);
            }
        }
    }
    if(res.dis < INF)
        puts(res.s.c_str());
    else
        puts("Stay home!");
}

int main() {
    while(scanf("%d%d", &n, &m) != EOF) {
        if(n == 0 && m == 0) break;
        getchar();
        for(int i = 0; i < n; ++i) gets(mat[i]);
        findAllStar();
        for(int i = 0; i <= ww; ++i)
            bfs(rr[i], cc[i], dis[i]);
        solve();
        print();
    }
}
