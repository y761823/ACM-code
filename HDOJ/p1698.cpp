////////////////////System Comment////////////////////
////Welcome to Hangzhou Dianzi University Online Judge
////http://acm.hdu.edu.cn
//////////////////////////////////////////////////////
////Username: y761823
////Nickname: Oyk
////Run ID: 
////Submit time: 2014-08-15 15:25:23
////Compiler: GUN C++
//////////////////////////////////////////////////////
////Problem ID: 1698
////Problem Title: 
////Run result: Accept
////Run time:906MS
////Run memory:2392KB
//////////////////System Comment End//////////////////
#include <cstdio>
#include <algorithm>
#include <iostream>
#include <cstring>
using namespace std;
typedef long long LL;

const int MAXN = 100010;
const int MAXT = MAXN << 2;

int a[MAXN], n, m, T;
int val[MAXT], sum[MAXT];

#define ll (x << 1)
#define rr (ll | 1)
#define mid ((l + r) >> 1)
void update(int x) {
    sum[x] = sum[ll] + sum[rr];
}

void pushdown(int x, int l, int r) {
    if(val[x]) {
        val[ll] = val[rr] = val[x];
        sum[ll] = (mid - l + 1) * val[x];
        sum[rr] = (r - mid) * val[x];
        val[x] = 0;
    }
}

void modify(int x, int l, int r, int a, int b, int k) {
    if(a <= l && r <= b) {
        val[x] = k;
        sum[x] = (r - l + 1) * k;
    } else {
        pushdown(x, l, r);
        if(a <= mid) modify(ll, l, mid, a, b, k);
        if(mid < b) modify(rr, mid + 1, r, a, b, k);
        update(x);
    }
}

int main() {
    scanf("%d", &T);
    for(int t = 1; t <= T; ++t) {
        scanf("%d%d", &n, &m);
        val[1] = 1;
        for(int i = 0, x, y, z; i < m; ++i) {
            scanf("%d%d%d", &x, &y, &z);
            modify(1, 1, n, x, y, z);
        }
        printf("Case %d: The total value of the hook is %d.\n", t, sum[1]);
    }
}