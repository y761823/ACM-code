////////////////////System Comment////////////////////
////Welcome to Hangzhou Dianzi University Online Judge
////http://acm.hdu.edu.cn
//////////////////////////////////////////////////////
////Username: y761823
////Nickname: Oyk
////Run ID: 
////Submit time: 2014-09-25 22:20:02
////Compiler: GUN C++
//////////////////////////////////////////////////////
////Problem ID: 5032
////Problem Title: 
////Run result: Accept
////Run time:2187MS
////Run memory:18336KB
//////////////////System Comment End//////////////////
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
#include <bitset>
using namespace std;
typedef long long LL;
typedef pair<int, int> PII;

const int MAXN = 1010;
const int MAXM = 100010;

struct Point {
    int a, x, y, id;
    void read(int i) {
        id = i;
        scanf("%d%d%d", &x, &y, &a);
    }
    Point() {}
    Point(int x, int y): x(x), y(y) {}
    int get();
    bool operator < (const Point &rhs) const {
        return y * rhs.x < rhs.y * x;
    }
    bool operator <= (const Point &rhs) const {
        return y * rhs.x <= rhs.y * x;
    }
} p[MAXN * MAXN], q[MAXM];

LL ans[MAXM];
int A, B;
int T, n = 1000, m, cnt;

int Point::get() {
    return (x + A) * (y + B);
}

LL tree[MAXN];

inline int lowbit(int x) {
    return x & -x;
}

void modify(int k, int val) {
    while(k <= n) {
        tree[k] += val;
        k += lowbit(k);
    }
}

LL get_sum(int k) {
    LL res = 0;
    while(k) {
        res += tree[k];
        k -= lowbit(k);
    }
    return res;
}

void solve() {
    memset(tree, 0, sizeof(tree));
    for(int i = 0, j = 0; i < m; ++i) {
        while(j < cnt && p[j] <= q[i]) {
            modify(p[j].x, p[j].get());
            j++;
        }
        ans[q[i].id] = get_sum(q[i].a);
    }
    for(int i = 0; i < m; ++i)
        printf("%I64d\n", ans[i]);
}

int main() {
    for(int i = 1; i <= n; ++i)
        for(int j = 1; j <= n; ++j) p[cnt++] = Point(i, j);
    sort(p, p + cnt);

    scanf("%d", &T);
    for(int t = 1; t <= T; ++t) {
        scanf("%d%d", &A, &B);
        scanf("%d", &m);
        for(int i = 0; i < m; ++i) q[i].read(i);
        sort(q, q + m);
        printf("Case #%d:\n", t);
        solve();
    }
}
