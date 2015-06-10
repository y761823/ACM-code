#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;

const int MAXN = 100010;

int fa[MAXN];
bool rela[MAXN];

int get_set(int x) {
    if(x == fa[x]) return x;
    else {
        int ret = get_set(fa[x]);
        rela[x] ^= rela[fa[x]];
        return fa[x] = ret;
    }
}

void unionSet(int x, int y) {
    int fx = get_set(x);
    int fy = get_set(y);
    fa[fy] = fx;
    rela[fy] = 1 ^ (rela[x] ^ rela[y]);
}

void query(int x, int y) {
    int fx = get_set(x);
    int fy = get_set(y);
    if(fx != fy) puts("Not sure yet.");
    else if(rela[x] == rela[y]) puts("In the same gang.");
    else puts("In different gangs.");
}

int main() {
    int T, n, m, x, y;
    char c;
    scanf("%d", &T);
    while(T--) {
        scanf("%d%d", &n, &m);
        for(int i = 1; i <= n; ++i)
            fa[i] = i, rela[i] = 0;
        while(m--) {
            scanf(" %c%d%d", &c, &x, &y);
            if(c == 'D') unionSet(x, y);
            else query(x, y);
        }
    }
}
