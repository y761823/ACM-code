#include <cstdio>
#include <iostream>
#include <algorithm>
#include <cstring>
#include <cmath>
using namespace std;
typedef long long LL;

const int SIZEH = 65537;

struct hash_map {
    int head[SIZEH], size;
    int next[SIZEH];
    LL state[SIZEH], val[SIZEH];

    void init() {
        memset(head, -1, sizeof(head));
        size = 0;
    }

    void insert(LL st, LL sv) {
        LL h = st % SIZEH;
        for(int p = head[h]; ~p; p = next[p])
            if(state[p] == st) return ;
        state[size] = st; val[size] = sv;
        next[size] = head[h]; head[h] = size++;
    }

    LL find(LL st) {
        LL h = st % SIZEH;
        for(int p = head[h]; ~p; p = next[p])
            if(state[p] == st) return val[p];
        return -1;
    }
} hashmap;

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

LL pow_mod(LL x, LL p, LL n) {
    LL ret = 1;
    while(p) {
        if(p & 1) ret = (ret * x) % n;
        x = (x * x) % n;
        p >>= 1;
    }
    return ret;
}

LL BabyStep_GiantStep(LL a, LL b, LL n) {
    for(LL i = 0, e = 1; i <= 64; ++i) {
        if(e == b) return i;
        e = (e * a) % n;
    }
    LL k = 1, cnt = 0;
    while(true) {
        LL t = __gcd(a, n);
        if(t == 1) break;
        if(b % t != 0) return -1;
        n /= t; b /= t; k = (k * a / t) % n;
        ++cnt;
    }
    hashmap.init();
    hashmap.insert(1, 0);
    LL e = 1, m = LL(ceil(sqrt(n + 0.5)));
    for(int i = 1; i < m; ++i) {
        e = (e * a) % n;
        hashmap.insert(e, i);
    }
    LL p = inv(pow_mod(a, m, n), n), v = inv(k, n);
    for(int i = 0; i < m; ++i) {
        LL t = hashmap.find((b * v) % n);
        if(t != -1) return i * m + t + cnt;
        v = (v * p) % n;
    }
    return -1;
}

int main() {
    LL x, z, k;
    while(cin>>x>>z>>k) {
        if(x == 0 && z == 0 && k == 0) break;
        LL ans = BabyStep_GiantStep(x % z, k % z, z);
        if(ans == -1) puts("No Solution");
        else cout<<ans<<endl;
    }
}
