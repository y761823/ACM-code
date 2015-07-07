////////////////////System Comment////////////////////
////Welcome to Hangzhou Dianzi University Online Judge
////http://acm.hdu.edu.cn
//////////////////////////////////////////////////////
////Username: y761823
////Nickname: Oyk
////Run ID: 
////Submit time: 2014-09-21 23:24:55
////Compiler: GUN C++
//////////////////////////////////////////////////////
////Problem ID: 5040
////Problem Title: 
////Run result: Accept
////Run time:250MS
////Run memory:5736KB
//////////////////System Comment End//////////////////
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <iostream>
#include <queue>
using namespace std;
typedef long long LL;
#define FOR(i, t) for(int i = 1; i <= t; ++i)

const int MAXN = 510;

char mat[MAXN][MAXN];
bool type[MAXN][MAXN][4];
int n, T, sr, sc, er, ec;

int fx[] = {-1, 0, 1, 0};
int fy[] = {0, 1, 0, -1};

int get(char c, int s) {
    if(c == 'N') s += 0;
    if(c == 'E') s += 1;
    if(c == 'S') s += 2;
    if(c == 'W') s += 3;
    if(s >= 4) s -= 4;
    return s;
}

bool isF(char c) {
    return c == 'N' || c == 'S' || c == 'E' || c == 'W';
}

void print(int t) {
    FOR(i, n) {
        FOR(j, n) printf("%d", type[i][j][t]);
        puts("");
    }
}

void init() {
    FOR(i, n) FOR(j, n) {
        if(mat[i][j] == 'M') sr = i, sc = j;
        if(mat[i][j] == 'T') er = i, ec = j;
    }
    memset(type, 0, sizeof(type));
    FOR(i, n) FOR(j, n) {
        if(isF(mat[i][j])) for(int s = 0; s < 4; ++s) {
            int f = get(mat[i][j], s);
            int r = i, c = j;
            for(int k = 0; k < 2; ++k) {
                if(mat[r][c] == 0) break;
                type[r][c][s] = true;
                r += fx[f], c += fy[f];
            }
        }
    }
    //print(2);
}

int dis[MAXN][MAXN][4];
struct Node {
    int r, c, s, d;
    Node() {}
    Node(int r, int c, int s, int d): r(r), c(c), s(s), d(d) {}
    bool ok() const {
        return dis[r][c][s] == d;
    }
    bool operator < (const Node &rhs) const {
        return d > rhs.d;
    }
};

int solve() {
    memset(dis, 0x3f, sizeof(dis));
    dis[sr][sc][0] = 0;
    priority_queue<Node> que;
    que.push(Node(sr, sc, 0, 0));
    while(!que.empty()) {
        Node u = que.top(); que.pop();
        if(!u.ok()) continue;
        if(u.r == er && u.c == ec)
            return u.d;

        int s = (u.s + 1) % 4;
        if(u.d + 1 < dis[u.r][u.c][s]) {
            dis[u.r][u.c][s] = u.d + 1;
            que.push(Node(u.r, u.c, s, u.d + 1));
        }
        for(int f = 0; f < 4; ++f) {
            int r = u.r + fx[f], c = u.c + fy[f], s = (u.s + 1) % 4, d = u.d + 1;
            if(mat[r][c] == '#' || mat[r][c] == 0) continue;
            if(type[u.r][u.c][u.s] || type[r][c][u.s]) d += 2, s = (s + 2) % 4;
            if(d < dis[r][c][s]) {
                dis[r][c][s] = d;
                que.push(Node(r, c, s, d));
            }
        }
    }
    return -1;
}

int main() {
    scanf("%d", &T);
    for(int t = 1; t <= T; ++t) {
        scanf("%d", &n);
        memset(mat, 0, sizeof(mat));
        for(int i = 1; i <= n; ++i) scanf("%s", &mat[i][1]);
        init();
        printf("Case #%d: %d\n", t, solve());
    }
}