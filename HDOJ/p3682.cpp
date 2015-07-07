////////////////////System Comment////////////////////
////Welcome to Hangzhou Dianzi University Online Judge
////http://acm.hdu.edu.cn
//////////////////////////////////////////////////////
////Username: y761823
////Nickname: Oyk
////Run ID: 
////Submit time: 2014-03-23 20:31:28
////Compiler: GUN C++
//////////////////////////////////////////////////////
////Problem ID: 3682
////Problem Title: 
////Run result: Accept
////Run time:15MS
////Run memory:336KB
//////////////////System Comment End//////////////////
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;

const int MAXN = 1010;

int n, m, T;

bool check(int t) {
    return 1 <= t && t <= n;
}

struct Node {
    int x, y, z;
    void set(char c, int d) {
        if(c == 'X') x = d;
        if(c == 'Y') y = d;
        if(c == 'Z') z = d;
    }
    void read() {
        char c1, c2;
        int a1, a2;
        scanf(" %c=%d,%c=%d", &c1, &a1, &c2, &a2);
        x = y = z = -1;
        if(check(a1) && check(a2)) {
            set(c1, a1);
            set(c2, a2);
        }
    }
    bool operator < (const Node &rhs) const {
        if(x != rhs.x) return x < rhs.x;
        if(y != rhs.y) return y < rhs.y;
        return z < rhs.z;
    }
    bool operator == (const Node &rhs) const {
        return x == rhs.x && y == rhs.y && z == rhs.z;
    }
    bool useless() {
        return x == -1 && y == -1 && z == -1;
    }
} p[MAXN];

bool Xdel[MAXN], Ydel[MAXN];

int solve(int z) {
    memset(Xdel, 0, sizeof(Xdel));
    memset(Ydel, 0, sizeof(Ydel));
    for(int i = 0; i < m; ++i) {
        if(p[i].z != z) continue;
        if(p[i].x != -1) {
            Xdel[p[i].x] = true;
        } else if(p[i].y != -1) {
            Ydel[p[i].y] = true;
        }
    }
    int cnt = 0, Xcnt = 0, Ycnt = 0;
    for(int i = 1; i <= n; ++i)
        Xcnt += Xdel[i], Ycnt += Ydel[i];
    for(int i = 0; i < m; ++i) {
        if(p[i].x != -1 && p[i].y != -1)
            cnt += (!Xdel[p[i].x] && !Ydel[p[i].y]);
    }
    return n * Xcnt + n * Ycnt - Xcnt * Ycnt + cnt;
}

int main() {
    scanf("%d", &T);
    while(T--) {
        scanf("%d%d", &n, &m);
        for(int i = 0; i < m; ++i) p[i].read();
        sort(p, p + m);
        m = unique(p, p + m) - p;
        int ans = 0;
        for(int i = 1; i <= n; ++i)
            ans += solve(i);
        printf("%d\n", ans);
    }
}
