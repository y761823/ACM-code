////////////////////System Comment////////////////////
////Welcome to Hangzhou Dianzi University Online Judge
////http://acm.hdu.edu.cn
//////////////////////////////////////////////////////
////Username: y761823
////Nickname: Oyk
////Run ID: 
////Submit time: 2015-06-09 18:28:52
////Compiler: GUN C++
//////////////////////////////////////////////////////
////Problem ID: 5238
////Problem Title: 
////Run result: Accept
////Run time:2636MS
////Run memory:31452KB
//////////////////System Comment End//////////////////
#include <cstdio>
#include <iostream>
#include <algorithm>
#include <cstring>
#include <vector>
using namespace std;
typedef long long LL;
#define REP(i, n) for(int i = 0; i < n; ++i)

const int MAXN = 50010;
const int MAXT = 100010;
const int MOD = 29393;

int mod[] = {7, 13, 17, 19};
int ans[7][13][17][19];

char op; int rhs;
int T, n, m;

int power(int x, int p, int mo) {
    int res = 1;
    while(p) {
        if(p & 1) res = (res * x) % mo;
        x = (x * x) % mo;
        p >>= 1;
    }
    return res;
}

int root(int l, int r) {
    return (l + r) | (l != r);
}
#define x root(l, r)
#define mid ((l + r) >> 1)
#define ll root(l, mid)
#define rr root(mid + 1, r)
int tree[MAXT][4][19];

void update(int l, int r) {
    REP(i, 4) REP(j, mod[i])
        tree[x][i][j] = tree[rr][i][ tree[ll][i][j] ];
}

void setval(int l, int r) {
    scanf(" %c%d", &op, &rhs);
    if(op == '+') REP(i, 4) REP(j, mod[i]) tree[x][i][j] = (j + rhs) % mod[i];
    if(op == '*') REP(i, 4) REP(j, mod[i]) tree[x][i][j] = (j * rhs) % mod[i];
    if(op == '^') REP(i, 4) REP(j, mod[i]) tree[x][i][j] = power(j, rhs, mod[i]);
}

void build(int l, int r) {
    if(l == r) {
        setval(l, r);
    } else {
        build(l, mid);
        build(mid + 1, r);
        update(l, r);
    }
}

void modify(int l, int r, int a, int b) {
    if(l == r) {
        setval(l, r);
    } else {
        if(a <= mid) modify(l, mid, a, b);
        if(mid < b) modify(mid + 1, r, a, b);
        update(l, r);
    }
}

int main() {
    for(int i = 0; i < MOD; ++i)
        ans[i % 7][i % 13][i % 17][i % 19] = i;

    scanf("%d", &T);
    for(int t = 1; t <= T; ++t) {
        scanf("%d%d", &n, &m);
        build(0, n - 1);

        printf("Case #%d:\n", t);
        int r = root(0, n - 1);
        for(int i = 0, a, b; i < m; ++i) {
            scanf("%d%d", &a, &b);
            if(a == 1) {
                printf("%d\n", ans[tree[r][0][b % mod[0]]][tree[r][1][b % mod[1]]][tree[r][2][b % mod[2]]][tree[r][3][b % mod[3]]]);
            } else {
                modify(0, n - 1, b - 1, b - 1);
            }
        }
    }
}
