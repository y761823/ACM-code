////////////////////System Comment////////////////////
////Welcome to Hangzhou Dianzi University Online Judge
////http://acm.hdu.edu.cn
//////////////////////////////////////////////////////
////Username: y761823
////Nickname: Oyk
////Run ID: 
////Submit time: 2014-03-16 20:46:33
////Compiler: GUN C++
//////////////////////////////////////////////////////
////Problem ID: 2485
////Problem Title: 
////Run result: Accept
////Run time:468MS
////Run memory:324KB
//////////////////System Comment End//////////////////
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <queue>
using namespace std;

const int MAXN = 110;
const int MAXE = 4010;
const int INF = 0x3fff3fff;

int n, m, k, a, b, ans, ecnt;
int SP[MAXN][MAXN];
int head[MAXN], dis[MAXN], pre[MAXN];
int to[MAXE], next[MAXE];
bool del[MAXN];

void init() {
    memset(head, 0, sizeof(head));
    memset(del, 0, sizeof(del));
    ecnt = 2;
}

void add_edge(int u, int v) {
    to[ecnt] = v; next[ecnt] = head[u]; head[u] = ecnt++;
}

bool bfs() {
    memset(dis, 0x3f, sizeof(head));
    queue<int> que; que.push(1);
    dis[1] = 0;
    while(!que.empty()) {
        int u = que.front(); que.pop();
        for(int p = head[u]; p; p = next[p]) {
            int v = to[p];
            if(!del[v] && dis[v] > n) {
                dis[v] = dis[u] + 1;
                pre[v] = u;
                if(v == n) return dis[n] <= k;
                que.push(v);
            }
        }
    }
    return false;
}

bool flag;

void dfs(int dep) {
    if(!bfs()) {
        flag = true;
        return ;
    }
    if(dep > ans) return ;
    int u = pre[n], cnt = 0;
    while(u != 1) {
        SP[dep][cnt++] = u;
        u = pre[u];
    }
    for(int i = cnt - 1; i >= 0; --i) {
        del[SP[dep][i]] = true;
        dfs(dep + 1);
        del[SP[dep][i]] = false;
    }
}

int main() {
    while(scanf("%d%d%d", &n, &m, &k) != EOF) {
        if(n == 0 && m == 0 && k == 0) break;
        init();
        while(m--) {
            scanf("%d%d", &a, &b);
            add_edge(a, b);
        }
        flag = false;
        for(ans = 0; ans < n; ++ans) {
            dfs(1);
            if(flag) break;
        }
        printf("%d\n", ans);
    }
}