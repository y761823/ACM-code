////////////////////System Comment////////////////////
////Welcome to Hangzhou Dianzi University Online Judge
////http://acm.hdu.edu.cn
//////////////////////////////////////////////////////
////Username: y761823
////Nickname: Oyk
////Run ID: 
////Submit time: 2013-08-14 23:23:08
////Compiler: GUN C++
//////////////////////////////////////////////////////
////Problem ID: 2492
////Problem Title: 
////Run result: Accept
////Run time:281MS
////Run memory:924KB
//////////////////System Comment End//////////////////
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;
typedef long long LL;

const int MAXN = 20010;

struct Node {
    int val, id;
    bool operator < (const Node &rhs) const {
        return val < rhs.val;
    }
};

Node a[MAXN];
LL tree[MAXN], sum[MAXN];
int f[MAXN];
int n;

inline int lowbit(int x) {
    return x & -x;
}

inline LL get_sum(int k) {
    LL ret = 0;
    while(k > 0) {
        ret += tree[k];
        k -= lowbit(k);
    }
    return ret;
}

inline void modify(int k, LL x) {
    while(k <= n) {
        tree[k] += x;
        k += lowbit(k);
    }
}

LL solve() {
    memset(tree, 0, sizeof(tree));
    LL ret = 0;
    for(int i = 1; i <= n; ++i) {
        sum[i] = get_sum(f[i]);
        modify(f[i], 1);
    }
    memset(tree, 0, sizeof(tree));
    for(int i = 1; i <= n; ++i) {
        ret += get_sum(f[i]);
        modify(f[i], sum[i]);
    }
    memset(tree, 0, sizeof(tree));
    for(int i = n; i > 0; --i) {
        sum[i] = get_sum(f[i]);
        modify(f[i], 1);
    }
    memset(tree, 0, sizeof(tree));
    for(int i = n; i > 0; --i) {
        ret += get_sum(f[i]);
        modify(f[i], sum[i]);
    }
    return ret;
}

int main() {
    int T;
    scanf("%d", &T);
    while(T--) {
        scanf("%d", &n);
        for(int i = 1; i <= n; ++i) scanf("%d", &a[i].val), a[i].id = i;
        sort(a + 1, a + n + 1);
        for(int i = 1; i <= n; ++i) f[a[i].id] = i;
        //printf("%d\n", solve());
        cout<<solve()<<endl;
    }
}
