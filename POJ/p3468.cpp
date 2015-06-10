#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
typedef long long LL;

const int MAXN = 100010;

LL bit0[MAXN], bit1[MAXN];
int n, q;

inline int lowbit(int x) {
    return x & -x;
}

void modify(LL *bit, int k, LL val) {
    while(k <= n) {
        bit[k] += val;
        k += lowbit(k);
    }
}

LL get_sum(LL *bit, int k) {
    LL ret = 0;
    while(k) {
        ret += bit[k];
        k -= lowbit(k);
    }
    return ret;
}

void modify(int l, int r, LL val) {
    modify(bit0, l, - val * (l - 1));
    modify(bit1, l, val);
    modify(bit0, r + 1, val * r);
    modify(bit1, r + 1, -val);
}

LL get_sum(int l, int r) {
    LL sum1 = get_sum(bit1, l - 1) * (l - 1) + get_sum(bit0, l - 1);
    LL sum2 = get_sum(bit1, r) * r + get_sum(bit0, r);
    return sum2 - sum1;
}

int main() {
    int l, r, a;
    scanf("%d%d", &n, &q);
    for(int i = 1; i <= n; ++i)
        scanf("%d", &a), modify(i, i, a);
    while(q--) {
        char c;
        scanf(" %c", &c);
        if(c == 'C') {
            scanf("%d%d%d", &l, &r, &a);
            modify(l, r, a);
        } else {
            scanf("%d%d", &l, &r);
            printf("%I64d\n", get_sum(l, r));
        }
    }
}
