////////////////////System Comment////////////////////
////Welcome to Hangzhou Dianzi University Online Judge
////http://acm.hdu.edu.cn
//////////////////////////////////////////////////////
////Username: y761823
////Nickname: Oyk
////Run ID: 
////Submit time: 2014-05-27 23:43:14
////Compiler: GUN C++
//////////////////////////////////////////////////////
////Problem ID: 1728
////Problem Title: 
////Run result: Accept
////Run time:15MS
////Run memory:1104KB
//////////////////System Comment End//////////////////
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
#include <queue>
using namespace std;

const int MAXN = 110;

struct Node {
    int f, x, y;
    Node() {}
    Node(int f, int x, int y):
        f(f), x(x), y(y) {}
};

int fx[] = {-1, 0, 1, 0};
int fy[] = {0, 1, 0, -1};

int dis[4][MAXN][MAXN];
char mat[MAXN][MAXN];
int T, n, m;
int k, x1, y1, x2, y2;

bool solve() {
    memset(dis, 0x3f, sizeof(dis));
    queue<Node>* pre = new queue<Node>();
    queue<Node>* cur = new queue<Node>();
    int step = 0;
    for(int i = 0; i < 4; ++i) pre->push(Node(i, x1, y1));
    for(int i = 0; i < 4; ++i) dis[i][x1][y1] = 0;
    while(step <= k && !pre->empty()) {
        Node t = pre->front(); pre->pop();
        if(dis[t.f][t.x][t.y] != step) continue;
        if(t.x == x2 && t.y == y2) return true;
        for(int i = 0; i < 4; ++i) {
            if((t.f + 2) % 4 == i) continue;
            int x = t.x + fx[i], y = t.y + fy[i], d = dis[t.f][t.x][t.y] + (t.f != i);
            if(mat[x][y] == '.' && d < dis[i][x][y]) {
                dis[i][x][y] = d;
                if(t.f == i) pre->push(Node(i, x, y));
                else cur->push(Node(i, x, y));
            }
        }
        if(pre->empty()) {
            step++;
            swap(pre, cur);
        }
    }
    return false;
}

int main() {
    scanf("%d", &T);
    while(T--) {
        scanf("%d%d", &n, &m);
        memset(mat, 0, sizeof(mat));
        for(int i = 1; i <= n; ++i) scanf("%s", &mat[i][1]);
        scanf("%d%d%d%d%d", &k, &y1, &x1, &y2, &x2);
        puts(solve() ? "yes" : "no");
    }
}
