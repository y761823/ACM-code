#include <cstdio>
#include <algorithm>
#include <cstring>
#include <iostream>
#include <complex>
using namespace std;
typedef long long LL;

struct Circle {
    double x, y, z, r;
    void read() {
        scanf("%lf%lf%lf%lf", &x, &y, &z, &r);
    }
};

double dist(const Circle &a, const Circle &b) {
    double x = a.x - b.x, y = a.y - b.y, z = a.z - b.z;
    return max(0.0, sqrt(x * x + y * y + z * z) - a.r - b.r);
}

const int MAXN = 110;

Circle p[MAXN];
int n;

double mat[MAXN][MAXN], dis[MAXN];
bool vis[MAXN];

double prim() {
    for(int i = 1; i < n; ++i) dis[i] = 1e10;
    memset(vis, 0, n * sizeof(bool));
    double res = 0;
    while(true) {
        int u = -1;
        for(int i = 0; i < n; ++i) if(!vis[i])
            if(u == -1 || dis[i] < dis[u]) u = i;
        if(u == -1) break;
        vis[u] = true;
        res += dis[u];
        for(int i = 0; i < n; ++i) if(!vis[i])
            dis[i] = min(dis[i], mat[u][i]);
    }
    return res;
}

int main() {
    while(scanf("%d", &n) != EOF && n) {
        for(int i = 0; i < n; ++i) p[i].read();
        for(int i = 0; i < n; ++i)
            for(int j = 0; j < n; ++j) mat[i][j] = dist(p[i], p[j]);
        printf("%.3f\n", prim());
    }
}
