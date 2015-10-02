#include <cstdio>
#include <iostream>
#include <algorithm>
#include <cstring>
#include <cctype>
#include <queue>
using namespace std;
typedef long long LL;
#define FOR(i, s, t) for(int i = s; i <= t; ++i)
#define foreach(it, vec) for(__typeof(vec.begin()) it = vec.begin(); it != vec.end(); ++it)

const int MAXN = 55;
const int INF = 0x3f3f3f3f;

int fx[] = {1, 0, -1, 0};
int fy[] = {0, 1, 0, -1};

int dis[MAXN][MAXN][1024][2];
char mat[MAXN][MAXN], smat[10][MAXN][MAXN];
int cnt[1024], impact[MAXN][MAXN];
int n, m, s, sx, sy, ex, ey;

void find_pos(int &x, int &y, char c) {
    for(x = 0; x < n; ++x)
        for(y = 0; y < m; ++y)
            if(mat[x][y] == c) return ;
}

int initfloor(int x, int y) {
    return mat[x][y] == '^' || isupper(mat[x][y]);
}

int getid(char c) {
    if(islower(c)) return c - 'a';
    return c - 'A';
}

int getfloor(int x, int y, int z) {
    if(mat[x][y] == '#') return -1;
    return initfloor(x, y) ^ (cnt[z & impact[x][y]] & 1);
}

int solve() {
    memset(dis, 0x3f, sizeof(dis));
    queue<int> que;
    que.push(sx); que.push(sy); que.push(0); que.push(0);
    dis[sx][sy][0][0] = 0;
    while(!que.empty()) {
        int x = que.front(); que.pop();
        int y = que.front(); que.pop();
        int z = que.front(); que.pop();
        int ff = que.front(); que.pop();

        if(x == ex && y == ey)
            return dis[x][y][z][ff];

        for(int f = 0; f < 4; ++f) {
            int newx = x + fx[f], newy = y + fy[f], newf = (mat[newx][newy] == '|' ? ff : getfloor(newx, newy, z));
            if(ff == newf && dis[newx][newy][z][newf] == INF) {
                dis[newx][newy][z][newf] = dis[x][y][z][ff] + 1;
                que.push(newx); que.push(newy); que.push(z); que.push(newf);
            }
        }

        if(mat[x][y] == '|') {
            int newz = z ^ (1 << s), newf = ff ^ 1;
            if(dis[x][y][newz][newf] == INF) {
                dis[x][y][newz][newf] = dis[x][y][z][ff] + 1;
                que.push(x); que.push(y); que.push(newz); que.push(newf);
            }
        }

        if(isalpha(mat[x][y])) {
            int newz = z ^ (1 << getid(mat[x][y])), newf = getfloor(x, y, newz);
            if(dis[x][y][newz][newf] == INF) {
                dis[x][y][newz][newf] = dis[x][y][z][ff] + 1;
                que.push(x); que.push(y); que.push(newz); que.push(newf);
            }
        }
    }
    return -1;
}

int main() {
    for(int i = 1; i < 1024; ++i)
        cnt[i] = cnt[i >> 1] + (i & 1);

    scanf("%d%d", &m, &n);
    for(int i = 0; i < n; ++i)
        scanf("%s", mat[i]);

    scanf("%d", &s);
    for(int v = 0; v < s; ++v) {
        for(int i = 0; i < n; ++i)
            scanf("%s", smat[v][i]);
        for(int i = 0; i < n; ++i)
            for(int j = 0; j < m; ++j) if(smat[v][i][j] == '*')
                impact[i][j] |= (1 << v);
    }

    find_pos(sx, sy, '%');
    find_pos(ex, ey, '&');
    printf("%d\n", solve());
}
