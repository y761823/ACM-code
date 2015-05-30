#include <cstdio>
#include <algorithm>
#include <iostream>
#include <cstring>
#include <queue>
using namespace std;
typedef long long LL;

const int MAXN = 10010;
const int INF = 0x3f3f3f3f;

int key[MAXN], weight[MAXN], child[MAXN][2], size[MAXN];
int poi_cnt;//not use point

inline int newNode(int k) {
    int x = ++poi_cnt;
    key[x] = k;
    size[x] = 1;
    weight[x] = rand();
    child[x][0] = child[x][1] = 0;
    return x;
}

inline void update(int &x) {
    size[x] = size[child[x][0]] + size[child[x][1]] + 1;//size[0]=0
}

inline void rotate(int &x, int t) {
    int y = child[x][t];
    child[x][t] = child[y][t ^ 1];
    child[y][t ^ 1] = x;
    update(x); update(y);
    x = y;
}

void insert(int &x, int k) {
    if (x == 0) x = newNode(k);
    else {
        int t = (key[x] < k);
        insert(child[x][t], k);
        if (weight[child[x][t]] < weight[x]) rotate(x, t);
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
            x = child[x][0] + child[x][1];
        }
    }
    else remove(child[x][key[x] < k], k);
    if(x > 0) update(x);
}

int kth(int &x, int k) {
    if(x == 0 || k <= 0 || k > size[x]) return 0;
    int s = size[child[x][0]];
    if(k == s + 1) return key[x];
    if(k <= s) return kth(child[x][0], k);
    return kth(child[x][1], k - s - 1);
}

queue<int> que;
int T, n, rt;

void init() {
    while(!que.empty()) que.pop();
    rt = poi_cnt = 0;
}

int main() {
    int kase = 0;
    while(scanf("%d", &n) != EOF) {
        printf("Case #%d:\n", ++kase);
        init();

        char op[8];
        for(int i = 0, x; i < n; ++i) {
            scanf("%s", op);
            if(strcmp(op, "in") == 0) {
                scanf("%d", &x);
                que.push(x);
                insert(rt, x);
            }
            if(strcmp(op, "query") == 0) {
                printf("%d\n", kth(rt, size[rt] / 2 + 1));
            }
            if(strcmp(op, "out") == 0) {
                //remove(rt, kth(rt, size[rt]));
                remove(rt, que.front());
                que.pop();
            }
        }
    }
}
