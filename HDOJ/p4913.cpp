////////////////////System Comment////////////////////
////Welcome to Hangzhou Dianzi University Online Judge
////http://acm.hdu.edu.cn
//////////////////////////////////////////////////////
////Username: y761823
////Nickname: Oyk
////Run ID: 
////Submit time: 2014-09-02 17:19:37
////Compiler: GUN C++
//////////////////////////////////////////////////////
////Problem ID: 4913
////Problem Title: 
////Run result: Accept
////Run time:1468MS
////Run memory:5752KB
//////////////////System Comment End//////////////////
#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>
#include <functional>
using namespace std;
typedef long long LL;

const int MAXN = 100010;
const int MAXT = MAXN << 2;
const int INF = 0x3f3f3f3f;
const int MOD = 1e9 + 7;

#define mod(x) ((x) % MOD)

int inv(int a) {
    if(a == 1) return 1;
    return ((MOD - MOD / a) * inv(MOD % a)) % MOD;
}

int inv2 = inv(2);

int power(LL x, int p) {
    LL res = 1;
    while(p) {
        if(p & 1) res = res * x % MOD;
        x = x * x % MOD;
        p >>= 1;
    }
    return res;
}

struct Node {
    int a, b, id;
    void read() {
        scanf("%d%d", &a, &b);
    }
    bool operator < (const Node &rhs) const {
        return b > rhs.b;
    }
} s[MAXN];
bool cmpa(Node a, Node b) {
    return a.a > b.a;
}

LL pow2[MAXN];
int va[MAXN];
int n;

void init() {
    pow2[0] = 1;
    for(int i = 1; i < MAXN; ++i) pow2[i] = mod(pow2[i - 1] * 2);
}

#define ll (x << 1)
#define rr (ll | 1)
#define mid ((l + r) >> 1)
int size[MAXT], sum[MAXT], mul[MAXT];

void update(int x) {
    sum[x] = mod(sum[ll] + sum[rr]);
    size[x] = size[ll] + size[rr];
}

void pushdown(int x) {
    if(mul[x] > 1) {
        mul[ll] = mod((LL)mul[ll] * mul[x]);
        sum[ll] = mod((LL)sum[ll] * mul[x]);
        mul[rr] = mod((LL)mul[rr] * mul[x]);
        sum[rr] = mod((LL)sum[rr] * mul[x]);
        mul[x] = 1;
    }
}

void build(int x, int l, int r) {
    mul[x] = 1;
    if(l == r) {
        sum[x] = mod(pow2[n - l] * power(2, va[l]));
        size[x] = 1;
    } else {
        build(ll, l, mid);
        build(rr, mid + 1, r);
        update(x);
    }
}

void modify(int x, int l, int r, int a, int b, LL val) {
    if(a <= l && r <= b) {
        mul[x] = mod(mul[x] * val);
        sum[x] = mod(sum[x] * val);
    } else {
        pushdown(x);
        if(a <= mid) modify(ll, l, mid, a, b, val);
        if(mid < b) modify(rr, mid + 1, r, a, b, val);
        update(x);
    }
}

void erase(int x, int l, int r, int pos) {
    if(l == r) {
        mul[x] = sum[x] = size[x] = 0;
    } else {
        pushdown(x);
        if(pos <= mid) erase(ll, l, mid, pos);
        if(mid < pos) erase(rr, mid + 1, r, pos);
        update(x);
    }
}

int query(int x, int l, int r, int a, int b, int &kth) {
    if(a <= l && r <= b) {
        kth += size[x];
        return sum[x];
    } else {
        pushdown(x);
        int res = 0;
        if(a <= mid) res = mod(res + query(ll, l, mid, a, b, kth));
        if(mid < b) res = mod(res + query(rr, mid + 1, r, a, b, kth));
        return res;
    }
}

int solve() {
    build(1, 1, n);
    LL res = 0;
    for(int i = 1; i <= n; ++i) {
        erase(1, 1, n, s[i].id);
        modify(1, 1, n, 1, s[i].id, inv2);
        int k = 0;
        LL tmp = query(1, 1, n, 1, s[i].id, k);
        tmp = mod(tmp + mod(pow2[n - i - k] * power(2, s[i].a)));
        res = mod(res + mod(power(3, s[i].b) * tmp));
    }
    return res;
}

int main() {
    //cout<<2 * inv2<<endl;
    init();
    while(scanf("%d", &n) != EOF) {
        for(int i = 1; i <= n; ++i) {
            s[i].read();
            va[i] = s[i].a;
        }

        sort(s + 1, s + n + 1, cmpa);
        for(int i = 1; i <= n; ++i) s[i].id = i;
        sort(s + 1, s + n + 1);
        sort(va + 1, va + n + 1, greater<int>());

        printf("%d\n", solve());
    }
}