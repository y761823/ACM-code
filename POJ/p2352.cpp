#include <cstdio>
#include <algorithm>
#include <cstring>
#include <iostream>
#include <vector>
using namespace std;
typedef long long LL;

const int MAXN = 15010;
const int MAXV = 32010;
const int INF = 0x3f3f3f3f;

struct Point {
    int x, y;
    void read() {
        scanf("%d%d", &x, &y);
        x++;
    }
} p[MAXN];
int cnt[MAXN], n;

int tree[MAXV];

int lowbit(int x) {
    return x & -x;
}

int get_sum(int x) {
    int res = 0;
    while(x) {
        res += tree[x];
        x -= lowbit(x);
    }
    return res;
}

void modify(int x, int val) {
    while(x <= 32001) {
        tree[x] += val;
        x += lowbit(x);
    }
}

int main() {
    scanf("%d", &n);
    for(int i = 0; i < n; ++i)
        p[i].read();
    for(int i = 0; i < n; ++i) {
        cnt[get_sum(p[i].x)]++;
        modify(p[i].x, 1);
    }
    for(int i = 0; i < n; ++i)
        printf("%d\n", cnt[i]);
}
