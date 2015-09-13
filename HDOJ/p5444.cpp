#include <cstdio>
#include <algorithm>
#include <iostream>
#include <cstring>
using namespace std;
typedef long long LL;

const int MAXV = 1010;

int fa[MAXV], ll[MAXV], rr[MAXV];
int a[MAXV];
int n, q, T;

int dfs_tree(int prel, int midl, int size) {
    int rt = a[prel], ls = rt - midl, rs = size - ls - 1;
    if(ls > 0) {
        int son = dfs_tree(prel + 1, midl, ls);
        ll[rt] = son;
        fa[son] = rt;
    }
    if(rs > 0) {
        int son = dfs_tree(prel + ls + 1, midl + ls + 1, rs);
        rr[rt] = son;
        fa[son] = rt;
    }
    return rt;
}

char res[MAXV], op[] = "EW";

void print(int u) {
    int cnt = 0;
    while(u != a[1]) {
        res[cnt++] = op[rr[fa[u]] == u];
        u = fa[u];
    }
    res[cnt] = 0;
    reverse(res, res + cnt);
    printf("%s\n", res);
}

int main() {
    scanf("%d", &T);
    while(T--) {
        scanf("%d", &n);
        for(int i = 1; i <= n; ++i)
            scanf("%d", &a[i]);
        dfs_tree(1, 1, n);
        scanf("%d", &q);
        for(int i = 0, u; i < q; ++i) {
            scanf("%d", &u);
            print(u);
        }
    }
}
