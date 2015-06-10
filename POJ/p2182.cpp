#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;

const int MAXN = 8010;

int key[MAXN], weight[MAXN], child[MAXN][2], size[MAXN];
int stk[MAXN], top, cnt;

inline int new_node(int k) {
    int x = (top ? stk[top--] : ++cnt);
    key[x] = k;
    size[x] = 1;
    weight[x] = rand();
    child[x][0] = child[x][1] = 0;
    return x;
}

inline void update(int &x) {
    size[x] = size[child[x][0]] + size[child[x][1]] + 1;
}

inline void rotate(int &x, int t) {
    int y = child[x][t];
    child[x][t] = child[y][t ^ 1];
    child[y][t ^ 1] = x;
    update(x); update(y);
    x = y;
}

void insert(int &x, int k) {
    if(x == 0) x = new_node(k);
    else {
        int t = (key[x] < k);
        insert(child[x][t], k);
        if(weight[child[x][t]] < weight[x]) rotate(x, t);
    }
    update(x);
}

void remove(int &x, int k) {
    if(key[x] == k) {
        if(child[x][0] && child[x][1]) {
            int t = weight[child[x][0]] < weight[child[x][1]];
            rotate(x, t); remove(child[x][t ^ 1], k);
        }
        else {
            stk[++top] = x;
            x = child[x][0] + child[x][1];
        }
    }
    else remove(child[x][key[x] < k], k);
    if(x > 0) update(x);
}

int kth(int &x, int k) {
    if(x == 0 || k <= 0 || k > size[x]) return 0;
    int s = 0;
    if(child[x][0]) s = size[child[x][0]];
    if(k == s + 1) return key[x];
    if(k <= s) return kth(child[x][0], k);
    return kth(child[x][1], k - s - 1);
}

int ans[MAXN], pre[MAXN];

int main() {
    int n;
    scanf("%d", &n);
    pre[1] = 0;
    for(int i = 2; i <= n; ++i) scanf("%d", &pre[i]);
    int root = new_node(1);
    for(int i = 2; i <= n; ++i) insert(root, i);
    for(int i = n; i > 0; --i) {
        int t = kth(root, pre[i] + 1);
        ans[i] = t;
        remove(root, t);
    }
    for(int i = 1; i <= n; ++i)
        printf("%d\n", ans[i]);
}
