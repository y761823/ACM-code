#include <cstdio>
#include <iostream>
#include <algorithm>
#include <cstring>
#include <queue>
using namespace std;
typedef long long LL;

const int MAXN = 50010;

int fa[MAXN], rela[MAXN];
int n, k;

void init() {
    for(int i = 1; i <= n; ++i) {
        fa[i] = i;
        rela[i] = 0;
    }
}

int find_set(int x) {
    if(fa[x] == x) return x;
    int rt = find_set(fa[x]);
    rela[x] = (rela[x] + rela[fa[x]]) % 3;
    return fa[x] = rt;
}

bool check(int d, int x, int y) {
    if(x > n || y > n) return false;
    int fx = find_set(x), fy = find_set(y);
    if(fx == fy) {
        return (rela[y] + d) % 3 == rela[x];
    } else {
        fa[fy] = fx;
        rela[fy] = (rela[x] - rela[y] + 3 - d) % 3;
        return true;
    }
}

int main() {
    scanf("%d%d", &n, &k);
    init();
    int res = 0;
    for(int i = 0, d, x, y; i < k; ++i) {
        scanf("%d%d%d", &d, &x, &y);
        res += !check(d - 1, x, y);
    }
    printf("%d\n", res);
}
