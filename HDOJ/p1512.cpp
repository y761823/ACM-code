////////////////////System Comment////////////////////
////Welcome to Hangzhou Dianzi University Online Judge
////http://acm.hdu.edu.cn
//////////////////////////////////////////////////////
////Username: y761823
////Nickname: Oyk
////Run ID: 
////Submit time: 2014-03-16 20:39:35
////Compiler: GUN C++
//////////////////////////////////////////////////////
////Problem ID: 1512
////Problem Title: 
////Run result: Accept
////Run time:781MS
////Run memory:2576KB
//////////////////System Comment End//////////////////
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

const int MAXN = 100010;

int n, m;
int fa[MAXN];

int key[MAXN], child[MAXN][2], dist[MAXN];
int stk[MAXN], top, node_cnt;
int root[MAXN];

void init() {
    dist[0] = -1;
    top = node_cnt = 0;
}

int newNode(int k) {
    int x = top ? stk[top--] : ++node_cnt;
    dist[x] = 1; key[x] = k;
    child[x][0] = child[x][1] = 0;
    return x;
}

void maintain(int &x) {
    if(dist[child[x][0]] < dist[child[x][1]])
        swap(child[x][0], child[x][1]);
    dist[x] = dist[child[x][0]] + 1;
}

int merge(int &x, int &y) {
    if(x == 0) return y;
    if(y == 0) return x;
    if(key[y] > key[x]) swap(x, y);
    child[x][1] = merge(child[x][1], y);
    maintain(x);
    return x;
}

int del(int &x) {
    if(x != 0) {
        stk[++top] = x;
        return merge(child[x][0], child[x][1]);
    }
    return 0;
}

int getfather(int x) {
    return fa[x] == x ? x : fa[x] = getfather(fa[x]);
}

int merge2(int x, int y) {
    return fa[x] = y;
}

void solve(int u, int v) {
    int fu = getfather(u);
    int fv = getfather(v);
    if(fu == fv) {
        printf("-1\n");
        return ;
    }
    int p1 = newNode(key[root[fu]] / 2);
    int p2 = newNode(key[root[fv]] / 2);
    int p3 = del(root[fu]);
    int p4 = del(root[fv]);
    p3 = merge(p1, p3);
    p4 = merge(p2, p4);
    int x = merge2(fu, fv);
    root[x] = merge(p3, p4);
    printf("%d\n", key[root[x]]);
}

int main() {
    int k, u, v;
    while(scanf("%d", &n) != EOF) {
        init();
        for(int i = 1; i <= n; ++i) {
            scanf("%d", &k);
            root[i] = newNode(k);
            fa[i] = i;
        }
        scanf("%d", &m);
        while(m--) {
            scanf("%d%d", &u, &v);
            solve(u, v);
        }
    }
}