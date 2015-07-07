////////////////////System Comment////////////////////
////Welcome to Hangzhou Dianzi University Online Judge
////http://acm.hdu.edu.cn
//////////////////////////////////////////////////////
////Username: y761823
////Nickname: Oyk
////Run ID: 
////Submit time: 2014-09-20 20:50:47
////Compiler: GUN C++
//////////////////////////////////////////////////////
////Problem ID: 5023
////Problem Title: 
////Run result: Accept
////Run time:250MS
////Run memory:3184KB
//////////////////System Comment End//////////////////
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;

const int MAXN = 200010;
const int MAXT = MAXN << 2;

int tmp[MAXT], cnt;
int col[MAXT], sum[MAXT];
int n, m;

int hash(int x) {
    return lower_bound(tmp, tmp + cnt, x) - tmp + 1;
}

#define ll (x << 1)
#define rr (ll | 1)
#define mid ((l + r) >> 1)
void maintain(int x) {
    sum[x] = sum[ll] | sum[rr];
}

void pushdown(int x) {
    if(col[x]) {
        col[ll] = col[rr] = col[x];
        sum[ll] = sum[rr] = (1 << (col[x] - 1));
        col[x] = 0;
    }
}

void update(int x, int l, int r, int a, int b, int val) {
    if(a <= l && r <= b) {
        col[x] = val;
        sum[x] = (1 << (val - 1));
    } else {
        pushdown(x);
        if(a <= mid) update(ll, l, mid, a, b, val);
        if(mid < b) update(rr, mid + 1, r, a, b, val);
        maintain(x);
    }
}

void update(int a, int b, int val) {
    update(1, 1, cnt, a, b, val);
}

int query(int x, int l, int r, int a, int b) {
    if(a <= l && r <= b) {
        return sum[x];
    } else {
        pushdown(x);
        int res = 0;
        if(a <= mid) res |= query(ll, l, mid, a, b);
        if(mid < b) res |= query(rr, mid + 1, r, a, b);
        return res;
    }
}

void query(int a, int b) {
    int res = query(1, 1, cnt, a, b);
    bool flag = true;
    for(int i = 1; i <= 30; ++i) {
        if(res & (1 << (i - 1))) {
            if(!flag) putchar(' ');
            else flag = false;
            printf("%d", i);
        }
    }
    puts("");
}

struct Query {
    char op;
    int a, b, val;
    void read() {
        scanf(" %c", &op);
        scanf("%d%d", &a, &b);
        tmp[cnt++] = a; tmp[cnt++] = b;
        if(op == 'P') scanf("%d", &val);
    }
    void work() {
        a = hash(a); b = hash(b);
        if(op == 'P') update(a, b, val);
        if(op == 'Q') query(a, b);
    }
} ask[MAXT];

int main() {
    while(scanf("%d%d", &n, &m) != EOF) {
        if(n == 0 && m == 0) break;
        cnt = 0;
        for(int i = 0; i < m; ++i) ask[i].read();
        sort(tmp, tmp + cnt);
        cnt = unique(tmp, tmp + cnt) - tmp;
        update(1, cnt, 2);
        for(int i = 0; i < m; ++i) ask[i].work();
    }
}