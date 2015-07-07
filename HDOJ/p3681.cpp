////////////////////System Comment////////////////////
////Welcome to Hangzhou Dianzi University Online Judge
////http://acm.hdu.edu.cn
//////////////////////////////////////////////////////
////Username: y761823
////Nickname: Oyk
////Run ID: 
////Submit time: 2014-04-06 21:46:55
////Compiler: GUN C++
//////////////////////////////////////////////////////
////Problem ID: 3681
////Problem Title: 
////Run result: Accept
////Run time:250MS
////Run memory:6956KB
//////////////////System Comment End//////////////////
#include <cstdio>
#include <iostream>
#include <algorithm>
#include <cstring>
#include <queue>
using namespace std;
typedef long long LL;

const int MAXN = 1 << 16;
const int MAXV = 20;

int fx[] = {-1, 0, 1, 0};
int fy[] = {0, 1, 0, -1};

char mat[MAXV][MAXV];
int id[MAXV][MAXV], dis[MAXV][MAXV], Gcnt, Ycnt;
int n, m;

bool isOn(int state, int i) {
    return (state >> i) & 1;
}

int moveState(int state, int i) {
    return state ^ (1 << i);
}

bool atEnd(int state) {
    return state % (1 << Ycnt) == 0;
}

bool isGYF(char c) {
    return c == 'G' || c == 'Y' || c == 'F';
}

int vis[MAXV][MAXV];

void bfsdis(int x, int y) {
    memset(vis, 0x7f, sizeof(vis));
    vis[x][y] = 0;
    queue<pair<int, int> > que;
    que.push(make_pair(x, y));
    int st = id[x][y];
    while(!que.empty()) {
        int x = que.front().first, y = que.front().second; que.pop();
        if(isGYF(mat[x][y])) dis[st][id[x][y]] = vis[x][y];
        for(int i = 0; i < 4; ++i) {
            int tx = x + fx[i], ty = y + fy[i];
            if(mat[tx][ty] != 'D' && vis[x][y] + 1 < vis[tx][ty]) {
                vis[tx][ty] = vis[x][y] + 1;
                que.push(make_pair(tx, ty));
            }
        }
    }
}

void init() {
    Ycnt = 0;
    for(int i = 1; i <= n; ++i) {
        for(int j = 1; j <= m; ++j) {
            if(mat[i][j] != 'Y') continue;
            id[i][j] = Ycnt++;
        }
    }
    Gcnt = Ycnt;
    for(int i = 1; i <= n; ++i) {
        for(int j = 1; j <= m; ++j) {
            if(mat[i][j] != 'G') continue;
            id[i][j] = Gcnt++;
        }
    }
    for(int i = 1; i <= n; ++i) {
        for(int j = 1; j <= m; ++j) {
            if(mat[i][j] != 'F') continue;
            id[i][j] = Gcnt;
        }
    }
    memset(dis, 0x7f, sizeof(dis));
    for(int i = 1; i <= n; ++i) {
        for(int j = 1; j <= m; ++j) {
            if(!isGYF(mat[i][j])) continue;
            bfsdis(i, j);
        }
    }
}

int best[MAXN][MAXV];
bool inque[MAXN][MAXV];

bool check(int energy) {
    memset(inque, 0, sizeof(inque));
    memset(best, 0, sizeof(best));
    best[(1 << Gcnt) - 1][Gcnt] = energy;
    queue<pair<int, int> > que;
    que.push(make_pair((1 << Gcnt) - 1, Gcnt));
    while(!que.empty()) {
        int state = que.front().first, pos = que.front().second; que.pop();
        inque[state][pos] = false;
        for(int i = 0; i < Gcnt; ++i) {
            if(!isOn(state, i)) continue;
            int newState = moveState(state, i);
            if(i >= Ycnt) {
                if(best[state][pos] >= dis[pos][i] && best[newState][i] == 0) {
                    best[newState][i] = energy;
                    inque[newState][i] = true;
                    que.push(make_pair(newState, i));
                }
            } else {
                if(best[state][pos] - dis[pos][i] >= 0 && atEnd(newState)) return true;
                if(best[state][pos] - dis[pos][i] > best[newState][i]) {
                    best[newState][i] = best[state][pos] - dis[pos][i];
                    if(!inque[newState][i]) {
                        inque[newState][i] = true;
                        que.push(make_pair(newState, i));
                    }
                }
            }
        }
    }
    return false;
}

int solve() {
    if(Ycnt == 0) return 0;
    int st = Gcnt;
    for(int i = 0; i < Ycnt; ++i)
        if(dis[i][st] > 2014) return -1;
    int l = 1, r = dis[st][0];
    for(int i = 0; i < Ycnt - 1; ++i) r += dis[i][i + 1];
    while(l < r) {
        int mid = (l + r) >> 1;
        if(!check(mid)) l = mid + 1;
        else r = mid;
    }
    return l;
}

int main() {
    while(scanf("%d%d", &n, &m) != EOF) {
        if(n == 0 && m == 0) break;
        memset(mat, 'D', sizeof(mat));
        for(int i = 1; i <= n; ++i) scanf("%s", &mat[i][1]);
        init();
        printf("%d\n", solve());
    }
}
