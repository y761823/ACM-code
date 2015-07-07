////////////////////System Comment////////////////////
////Welcome to Hangzhou Dianzi University Online Judge
////http://acm.hdu.edu.cn
//////////////////////////////////////////////////////
////Username: y761823
////Nickname: Oyk
////Run ID: 
////Submit time: 2013-09-15 21:52:36
////Compiler: GUN C++
//////////////////////////////////////////////////////
////Problem ID: 4747
////Problem Title: 
////Run result: Accept
////Run time:1000MS
////Run memory:12340KB
//////////////////System Comment End//////////////////
#include <iostream>
#include <cstring>
#include <cstdio>
#include <algorithm>
using namespace std;
typedef long long LL;

#define ll x * 2
#define rr x * 2 + 1

const int MAXN = 200010;

LL tree[MAXN * 4];
int maxt[MAXN * 4], mint[MAXN * 4];
int a[MAXN], n;

int head[MAXN], lcnt;
int pos[MAXN], next[MAXN];

void init() {
    memset(head, 0, (n + 1) * sizeof(int));
    lcnt = 1;
}

void add_link(int x, int i) {
    pos[lcnt] = i; next[lcnt] = head[x]; head[x] = lcnt++;
}

void build(int x, int left, int right) {
    if(left == right) tree[x] = maxt[x] = mint[x] = n - left + 1;
    else {
        int mid = (left + right) >> 1;
        if(left <= mid) build(ll, left, mid);
        if(mid < right) build(rr, mid + 1, right);
        tree[x] = tree[ll] + tree[rr];
        maxt[x] = max(maxt[ll], maxt[rr]);
        mint[x] = min(mint[ll], mint[rr]);
    }
}

void update(int x, int left, int right, int a, int b, int val) {
    if(a <= left && right <= b && mint[x] >= val) {
        tree[x] = LL(val) * (right - left + 1);
        maxt[x] = mint[x] = val;
    }
    else {
        if(right == left) return ;
        int mid = (left + right) >> 1;
        if(maxt[x] == mint[x]) {
            maxt[ll] = mint[ll] = maxt[x];
            tree[ll] = LL(mid - left + 1) * maxt[x];
            maxt[rr] = mint[rr] = maxt[x];
            tree[rr] = LL(right - (mid + 1) + 1) * maxt[x];
        }
        if(a <= mid && maxt[ll] > val) update(ll, left, mid, a, b, val);
        if(mid < b && maxt[rr] > val) update(rr, mid + 1, right, a, b, val);
        tree[x] = tree[ll] + tree[rr];
        maxt[x] = max(maxt[ll], maxt[rr]);
        mint[x] = min(mint[ll], mint[rr]);
    }
}

LL solve() {
    LL ret = 0;
    build(1, 1, n);
    for(int i = 0; i <= n && tree[1]; ++i) {
        int last = 0;
        for(int p = head[i]; p; p = next[p]) {
            update(1, 1, n, last + 1, pos[p], n - pos[p] + 1);
            last = pos[p];
        }
        update(1, 1, n, last + 1, n, 0);
        ret += tree[1];
    }
    return ret;
}

int main() {
    while(scanf("%d", &n) != EOF && n) {
        for(int i = 1; i <= n; ++i) scanf("%d", &a[i]);
        init();
        for(int i = n; i > 0; --i) if(a[i] <= n) add_link(a[i], i);
        cout<<solve()<<endl;
    }
}
