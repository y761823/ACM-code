#include <cstdio>
#include <algorithm>
#include <cstring>
#include <iostream>
using namespace std;
typedef long long LL;

const int MAXN = 10010;
const int MAXT = MAXN << 1;
const int MAXP = 13;

int T, n, M, q;

LL power(LL x, LL p) {
    if(p < 0) return 0;
    LL res = 1;
    while(p) {
        if(p & 1) res = res * x % M;
        x = x * x % M;
        p >>= 1;
    }
    return res;
}


int root(int l, int r) { return (l + r) | (l != r); }
#define x root(l, r)
#define mid ((l + r) >> 1)
#define ll root(l, mid)
#define rr root(mid + 1, r)
struct SegmentTreeA {
    LL sum[MAXT], add[MAXT];

    void build(int l, int r) {
        if(l != r) {
            build(l, mid);
            build(mid + 1, r);
        }
        sum[x] = add[x] = 0;
    }

    void modify(int l, int r, int val) {
        add[x] += val;
        sum[x] += (r - l + 1) * val;
    }

    void pushdown(int l, int r) {
        if(add[x]) {
            modify(l, mid, add[x]);
            modify(mid + 1, r, add[x]);
            add[x] = 0;
        }
    }

    void update(int l, int r) {
        sum[x] = sum[ll] + sum[rr];
    }

    void modify_add(int l, int r, int a, int b, int val) {
        if(a <= l && r <= b) {
            modify(l, r, val);
        } else {
            pushdown(l, r);
            if(a <= mid) modify_add(l, mid, a, b, val);
            if(mid < b) modify_add(mid + 1, r, a, b, val);
            update(l, r);
        }
    }

    LL query(int l, int r, int a, int b) {
        if(a <= l && r <= b) {
            return sum[x];
        } else {
            pushdown(l, r);
            LL res = 0;
            if(a <= mid) res += query(l, mid, a, b);
            if(mid < b) res += query(mid + 1, r, a, b);
            return res;
        }
    }
} tree[MAXP];

struct SegmentTreeB {
    int prod[MAXT], mul[MAXT];

    void build(int l, int r) {
        if(l != r) {
            build(l, mid);
            build(mid + 1, r);
        }
        prod[x] = mul[x] = 1;
    }

    void modify(int l, int r, int val) {
        mul[x] = (LL)mul[x] * val % M;
        prod[x] = (LL)prod[x] * power(val, r - l + 1) % M;
    }

    void pushdown(int l, int r) {
        if(mul[x] != 1) {
            modify(l, mid, mul[x]);
            modify(mid + 1, r, mul[x]);
            mul[x] = 1;
        }
    }

    void update(int l, int r) {
        prod[x] = (LL)prod[ll] * prod[rr] % M;
    }

    void modify_mul(int l, int r, int a, int b, int val) {
        if(a <= l && r <= b) {
            modify(l, r, val);
        } else {
            pushdown(l, r);
            if(a <= mid) modify_mul(l, mid, a, b, val);
            if(mid < b) modify_mul(mid + 1, r, a, b, val);
            update(l, r);
        }
    }

    int query(int l, int r, int a, int b) {
        if(a <= l && r <= b) {
            return prod[x];
        } else {
            pushdown(l, r);
            int res = 1;
            if(a <= mid) res = (LL)res * query(l, mid, a, b) % M;
            if(mid < b) res = (LL)res * query(mid + 1, r, a, b) % M;
            return res;
        }
    }
} treec;
#undef x

void exgcd(LL a, LL b, LL &x, LL &y) {
    if(!b) x = 1, y = 0;
    else {
       exgcd(b, a % b, y, x);
        y -= x * (a / b);
   }
}

LL inv(LL a, LL n) {
    LL x, y;
    exgcd(a, n, x, y);
    return (x + n) % n;
}

int find_factor(int val, int p[]) {
    int cnt = 0;
    for(int i = 2; i * i <= val; ++i) {
        if(val % i == 0) {
            while(val % i == 0) {
                val /= i;
            }
            p[cnt++] = i;
        }
    }
    if(val > 1) p[cnt++] = val;
    return cnt;
}

int mp[MAXP], mcnt;

void modify(int l, int r, int val, int flag) {
    for(int i = 0; i < mcnt; ++i) {
        int v = mp[i], cnt = 0;
        while(val && val % v == 0) {
            val /= v;
            cnt++;
        }
        if(cnt) tree[i].modify_add(1, n, l, r, flag * cnt);
    }
    val %= M;
    if(val != 1) {
        if(flag == -1) val = inv(val, M);
        treec.modify_mul(1, n, l, r, val);
    }
}

int query(int l, int r) {
    int res = treec.query(1, n, l, r);
    for(int i = 0; i < mcnt; ++i)
        res = (LL)res * power(mp[i], tree[i].query(1, n, l, r)) % M;
    return res;
}

int main() {
    scanf("%d", &T);
    for(int t = 1; t <= T; ++t) {
        scanf("%d%d", &n, &M);

        mcnt = find_factor(M, mp);
        for(int i = 0; i < mcnt; ++i) tree[i].build(1, n);
        treec.build(1, n);

        for(int i = 1, a; i <= n; ++i) {
            scanf("%d", &a);
            modify(i, i, a, 1);
        }

        printf("Case #%d:\n", t);
        scanf("%d", &q);
        char op;
        for(int i = 0, l, r, x; i < q; ++i) {
            scanf(" %c%d%d", &op, &l, &r);
            if(op != 'Q') scanf("%d", &x);
            if(op == 'M') modify(l, r, x, 1);
            if(op == 'D') modify(l, r, x, -1);
            if(op == 'Q') printf("%d\n", query(l, r));
        }
    }
}
