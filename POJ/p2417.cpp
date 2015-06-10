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

LL inv(LL a, LL n) {
    if(a == 1) return 1;
    return ((n - n / a) * inv(n % a, n)) % n;
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

LL BabyStep(LL a, LL b, LL n) {
    LL e = 1, m = LL(ceil(sqrt(n + 0.5)));
    hashmap.init();
    hashmap.insert(1, 0);
    for(int i = 1; i < m; ++i) {
        e = (e * a) % n;
        hashmap.insert(e, i);
    }
    LL v = inv(pow_mod(a, m, n), n);
    for(int i = 0; i < m; ++i) {
        LL t = hashmap.find(b);
        if(t != -1) return i * m + t;
        b = (b * v) % n;
    }
    return -1;
}

int main() {
    LL p, b, n;
    while(cin>>p>>b>>n) {
        LL ans = BabyStep(b, n, p);
        if(ans == -1) puts("no solution");
        else cout<<ans<<endl;
    }
}