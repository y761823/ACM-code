////////////////////System Comment////////////////////
////Welcome to Hangzhou Dianzi University Online Judge
////http://acm.hdu.edu.cn
//////////////////////////////////////////////////////
////Username: y761823
////Nickname: Oyk
////Run ID: 
////Submit time: 2014-07-16 17:14:43
////Compiler: GUN C++
//////////////////////////////////////////////////////
////Problem ID: 1242
////Problem Title: 
////Run result: Accept
////Run time:15MS
////Run memory:652KB
//////////////////System Comment End//////////////////
#include <iostream>
#include <algorithm>
#include <cstring>
#include <cstdio>
#include <queue>
using namespace std;
typedef long long LL;

const int MAXN = 210;

char mat[MAXN][MAXN];
int dis[MAXN][MAXN], inque[MAXN][MAXN];
int n, m;
int sx, sy, ex, ey;

int fx[] = {-1, 0, 1, 0};
int fy[] = {0, 1, 0, -1};

int spfa() {
    queue<pair<int, int> > que;
    que.push(make_pair(sx, sy));
    memset(dis, 0x3f, sizeof(dis));
    dis[sx][sy] = 0;
    while(!que.empty()) {
        int x = que.front().first, y = que.front().second; que.pop();
        inque[x][y] = false;
        for(int i = 0; i < 4; ++i) {
            int nx = x + fx[i], ny = y + fy[i];
            if(mat[nx][ny] == '.' || mat[nx][ny] == 'x' || mat[nx][ny] == 'r') {
                int cost = 1 + (mat[nx][ny] == 'x');
                if(dis[x][y] + cost < dis[nx][ny]) {
                    dis[nx][ny] = dis[x][y] + cost;
                    if(!inque[nx][ny]) {
                        que.push(make_pair(nx, ny));
                        inque[nx][ny] = true;
                    }
                }
            }
        }
    }
    return dis[ex][ey];
}

int main() {
    while(scanf("%d%d", &n, &m) != EOF) {
        memset(mat, 0, sizeof(mat));
        for(int i = 1; i <= n; ++i)
            scanf("%s", &mat[i][1]);
        for(int i = 1; i <= n; ++i) {
            for(int j = 1; j <= m; ++j) {
                if(mat[i][j] == 'a') sx = i, sy = j;
                if(mat[i][j] == 'r') ex = i, ey = j;
            }
        }
        int ans = spfa();
        if(ans == 0x3f3f3f3f) puts("Poor ANGEL has to stay in the prison all his life.");
        else printf("%d\n", ans);
    }
}