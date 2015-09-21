#include <cstdio>
#include <iostream>
#include <algorithm>
#include <cstring>
using namespace std;
typedef long long LL;

const int MAXN = 46337 + 10;
const int INF = 0x3f3f3f3f;

int a[MAXN << 1];
LL x;
int m, T;

int init() {
    a[0] = 2 % m; a[1] = 10 % m;
    for(int i = 2; ; ++i) {
        a[i] = (10 * a[i - 1] - a[i - 2] + m) % m;
        if(a[i - 1] == a[0] && a[i] == a[1]) return i - 1;
    }
}

int power(LL x, LL p, int mod) {
    LL res = 1;
    while(p) {
        if(p & 1) res = res * x % mod;
        x = x * x % mod;
        p >>= 1;
    }
    return res;
}

int main() {
    scanf("%d", &T);
    for(int t = 1; t <= T; ++t) {
        scanf("%I64d%d", &x, &m);
        int cnt = init();
        int res = a[(power(2, x, cnt) + 1) % cnt];
        printf("Case #%d: %d\n", t, (res + m - 1) % m);
    }
}
