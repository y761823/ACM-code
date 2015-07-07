////////////////////System Comment////////////////////
////Welcome to Hangzhou Dianzi University Online Judge
////http://acm.hdu.edu.cn
//////////////////////////////////////////////////////
////Username: y761823
////Nickname: Oyk
////Run ID: 
////Submit time: 2014-04-07 18:23:56
////Compiler: GUN C++
//////////////////////////////////////////////////////
////Problem ID: 3688
////Problem Title: 
////Run result: Accept
////Run time:625MS
////Run memory:33616KB
//////////////////System Comment End//////////////////
#include <cstdio>
#include <iostream>
#include <algorithm>
#include <cstring>
#include <queue>
using namespace std;
typedef long long LL;

const int MAXN = 110;
const int MAXM = 11000;

struct Node {
    int a, x, y;
    bool operator < (const Node &rhs) const {
        if(a != rhs.a) return a < rhs.a;
        if(x != rhs.x) return x < rhs.x;
        return y < rhs.y;
    }
} p[MAXN * MAXM];

int mat[MAXN][MAXM];
int xfa[MAXM][MAXN], yfa[MAXN][MAXM];
int xsize[MAXM][MAXN], ysize[MAXN][MAXM];
int n, m, s;

void init() {
    for(int j = 1; j <= m; ++j)
        for(int i = 1; i <= n; ++i) xfa[j][i] = i, xsize[j][i] = 1;
    for(int i = 1; i <= n; ++i)
        for(int j = 1; j <= m; ++j) yfa[i][j] = j, ysize[i][j] = 1;
}

int find_set(int *fa, int x) {
    return fa[x] == x ? x : fa[x] = find_set(fa, fa[x]);
}

void merge(int *fa, int *size, int x, int y) {
    int fx = find_set(fa, x), fy = find_set(fa, y);
    if(size[fx] < size[fy]) swap(fx, fy);
    size[fx] += size[fy];
    fa[fy] = fx;
}

int solve() {
    int largest = 0;
    for(int k = 0, i = 0; i < s; ++k) {
        if(k - 1 >= largest) return k;
        while(i < s && p[i].a == k) {
            int x = p[i].x, y = p[i].y;
            if(x - 1 >= 1 && mat[x - 1][y] <= k) merge(xfa[y], xsize[y], x - 1, x);
            if(x + 1 <= n && mat[x + 1][y] < k) merge(xfa[y], xsize[y], x, x + 1);
            if(y - 1 >= 1 && mat[x][y - 1] <= k) merge(yfa[x], ysize[x], y - 1, y);
            if(y + 1 <= m && mat[x][y + 1] < k) merge(yfa[x], ysize[x], y, y + 1);

            int fx = find_set(xfa[y], x), fy = find_set(yfa[x], y);
            if(xsize[y][fx] == n || ysize[x][fy] == m) return -1;

            if(find_set(xfa[y], 1) == fx || find_set(xfa[y], n) == fx)
                largest = max(largest, xsize[y][fx]);
            else largest = max(largest, (xsize[y][fx] + 1) / 2);
            if(find_set(yfa[x], 1) == fy || find_set(yfa[x], m) == fy)
                largest = max(largest, ysize[x][fy]);
            else largest = max(largest, (ysize[x][fy] + 1) / 2);

            ++i;
        }
    }
    return -1;
}

int main() {
    while(scanf("%d%d", &n, &m) != EOF) {
        if(n == 0 && m == 0) break;
        s = 0;
        for(int i = 1; i <= n; ++i) {
            for(int j = 1; j <= m; ++j) {
                scanf("%d", &mat[i][j]);
                p[s].x = i;
                p[s].y = j;
                p[s++].a = mat[i][j];
            }
        }
        sort(p, p + s);
        init();
        int ans = solve();
        if(ans == -1) puts("NO ANSWER!");
        else printf("%d\n", ans);
    }
}
