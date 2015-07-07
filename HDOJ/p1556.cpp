////////////////////System Comment////////////////////
////Welcome to Hangzhou Dianzi University Online Judge
////http://acm.hdu.edu.cn
//////////////////////////////////////////////////////
////Username: y761823
////Nickname: Oyk
////Run ID: 
////Submit time: 2014-08-15 15:26:17
////Compiler: GUN C++
//////////////////////////////////////////////////////
////Problem ID: 1556
////Problem Title: 
////Run result: Accept
////Run time:656MS
////Run memory:712KB
//////////////////System Comment End//////////////////
#include <cstdio>
#include <algorithm>
#include <iostream>
#include <cstring>
using namespace std;
typedef long long LL;

const int MAXN = 100010;

int tree[MAXN], n;

inline int lowbit(int x) {
    return x & -x;
}

void modify(int k, int val) {
    while(k <= n) {
        tree[k] += val;
        k += lowbit(k);
    }
}

int get_sum(int k) {
    int res = 0;
    while(k) {
        res += tree[k];
        k -= lowbit(k);
    }
    return res;
}

int main() {
    while(scanf("%d", &n) != EOF && n) {
        memset(tree + 1, 0, n * sizeof(int));
        for(int i = 0, a, b; i < n; ++i) {
            scanf("%d%d", &a, &b);
            modify(a, 1); modify(b + 1, -1);
        }
        for(int i = 1; i < n; ++i)
            printf("%d ", get_sum(i));
        printf("%d\n", get_sum(n));
    }
}