////////////////////System Comment////////////////////
////Welcome to Hangzhou Dianzi University Online Judge
////http://acm.hdu.edu.cn
//////////////////////////////////////////////////////
////Username: y761823
////Nickname: Oyk
////Run ID: 
////Submit time: 2013-10-03 23:01:38
////Compiler: GUN C++
//////////////////////////////////////////////////////
////Problem ID: 4435
////Problem Title: 
////Run result: Accept
////Run time:31MS
////Run memory:444KB
//////////////////System Comment End//////////////////
#include <cstdio>
#include <iostream>
#include <algorithm>
#include <cstring>
#include <cmath>
#include <queue>
using namespace std;
typedef long long LL;

const int MAXN = 150;

struct Point {
    double x, y;
    void read() {
        scanf("%lf%lf", &x, &y);
    }
};

int dist(const Point &a, const Point &b) {
    return (int)ceil(sqrt((a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y)));
}

Point a[MAXN];
int mat[MAXN][MAXN], n, d;
int select[MAXN];
bool vis[MAXN];

bool check() {
    memset(vis, 0, sizeof(vis));
    queue<int> que;
    que.push(1); vis[1] = true;
    while(!que.empty()) {
        int u = que.front(); que.pop();
        for(int v = 1; v <= n; ++v) {
            if(vis[v]) continue;
            if(mat[u][v] * 2 <= d) vis[v] = true;
            if(mat[u][v] <= d && select[v]) {
                que.push(v);
                vis[v] = true;
            }
        }
    }
    for(int i = 1; i <= n; ++i) if(!vis[i]) return false;
    return true;
}

bool solve() {
    for(int i = 1; i <= n; ++i) select[i] = 1;
    if(!check()) return false;
    for(int i = n; i > 1; --i) {
        select[i] = false;
        if(!check()) select[i] = true;
    }
    return true;
}

void print() {
    bool flag = false;
    for(int i = n; i > 0; --i) {
        if(!flag && !select[i]) continue;
        printf("%d", select[i]);
        flag = true;
    }
    puts("");
}

int main() {
    while(scanf("%d%d", &n, &d) != EOF) {
        for(int i = 1; i <= n; ++i) a[i].read();
        for(int i = 1; i <= n; ++i)
            for(int j = i; j <= n; ++j) mat[i][j] = mat[j][i] = dist(a[i], a[j]);
        if(solve()) print();
        else puts("-1");
    }
}
