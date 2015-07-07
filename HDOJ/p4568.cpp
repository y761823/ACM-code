////////////////////System Comment////////////////////
////Welcome to Hangzhou Dianzi University Online Judge
////http://acm.hdu.edu.cn
//////////////////////////////////////////////////////
////Username: y761823
////Nickname: Oyk
////Run ID: 
////Submit time: 2013-08-21 22:37:43
////Compiler: GUN C++
//////////////////////////////////////////////////////
////Problem ID: 4568
////Problem Title: 
////Run result: Accept
////Run time:171MS
////Run memory:1912KB
//////////////////System Comment End//////////////////
#include <cstdio>
#include <queue>
#include <utility>
#include <iostream>
#include <cstring>
using namespace std;
typedef pair<int, int> PII;

const int MAXN = 205;

int mat[MAXN][MAXN], tx[15], ty[15];
int dis[MAXN][MAXN], di[15][15];
bool ist[MAXN][MAXN];
int post[MAXN][MAXN];
int n, m, k;

#define pos(x, y) (x*MAXN+y)

int fx[4] = {-1,0,1,0};
int fy[4] = {0,1,0,-1};

void min_path(int st_x, int st_y, int now) {
    priority_queue<PII> que;
    que.push(make_pair(-mat[st_x][st_y], pos(st_x, st_y)));
    memset(dis, 0x3f, sizeof(dis));
    dis[st_x][st_y] = mat[st_x][st_y];
    while(!que.empty()) {
        int abc = -que.top().first, tmp = que.top().second; que.pop();
        int x = tmp / MAXN, y = tmp % MAXN;
        if(abc != dis[x][y]) continue;
        for(int i = 0; i < 4; ++i) {
            int newx = x + fx[i], newy = y + fy[i];
            if(0 <= newx && newx < n && 0 <= newy && newy < m) {
                if(mat[newx][newy] == -1) continue;
                if(dis[newx][newy] > mat[newx][newy] + dis[x][y]) {
                    dis[newx][newy] = mat[newx][newy] + dis[x][y];
                    que.push(make_pair(-dis[newx][newy], pos(newx, newy)));
                    if(ist[newx][newy] && dis[newx][newy] < di[now][post[newx][newy]])
                        di[now][post[newx][newy]] = dis[newx][newy];
                }
            }
            else if(dis[x][y] < di[now][k]) di[now][k] = dis[x][y];
        }
    }
}

int dp[14][20000];
int ans, sum;

int dfs(int u, int use) {
    if(dp[u][use] < 0x3f3f3f3f) return dp[u][use];
    if(use == 0) {
        return dp[u][use] = di[u][k];
    }
    for(int i = 0; i < k; ++i) {
        if(use & (1 << i))
            dp[u][use] = min(dp[u][use], di[u][i] + dfs(i, use ^ (1 << i)));
    }
    return dp[u][use];
}

void solve() {
    memset(dp, 0x3f, sizeof(dp));
    ans = 0x7fff7fff;
    for(int i = 0; i < k; ++i)
        ans = min(ans, di[i][k] + dfs(i, (1 << i) ^ ((1 << k) - 1)));
}

void printdi() {
    for(int i = 0; i < k; ++i) {
        for(int j = 0; j <= k; ++j) printf("%d ", di[i][j]);
        printf("\n");
    }
}

int main() {
    int T;
    scanf("%d", &T);
    while(T--) {
        scanf("%d%d", &n, &m);
        for(int i = 0; i < n; ++i)
            for(int j = 0; j < m; ++j) scanf("%d", &mat[i][j]);
        scanf("%d", &k);
        memset(ist, 0, sizeof(ist));
        sum = 0;
        for(int i = 0; i < k; ++i) {
            scanf("%d%d", &tx[i], &ty[i]);
            ist[tx[i]][ty[i]] = true;
            post[tx[i]][ty[i]] = i;
            sum += mat[tx[i]][ty[i]];
        }
        memset(di, 0x3f, sizeof(di));
        for(int i = 0; i < k; ++i) min_path(tx[i], ty[i], i);
        //printdi();
        solve();
        printf("%d\n", ans - sum);
    }
}
