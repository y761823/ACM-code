#include <cstdio>
#include <algorithm>
#include <cstring>
#include <iostream>
#include <vector>
using namespace std;
typedef long long LL;

const int MAXN = 1025;
const int INF = 0x3f3f3f3f;

int tree[MAXN][MAXN];
int s;

int lowbit(int x) {
    return x & -x;
}

void modify(int _x, int _y, int v) {
    for(int x = _x; x <= s; x += lowbit(x))
        for(int y = _y; y <= s; y += lowbit(y))
            tree[x][y] += v;
}

int getSum(int _x, int _y) {
    int res = 0;
    for(int x = _x; x; x -= lowbit(x))
        for(int y = _y; y; y -= lowbit(y))
            res += tree[x][y];
    return res;
}

int main() {
    scanf("%*d%d", &s);
    int op, a, b, c, d;
    while(scanf("%d", &op) != EOF) {
        if(op == 3) break;
        if(op == 1) {
            scanf("%d%d%d", &a, &b, &c);
            modify(a + 1, b + 1, c);
        }
        if(op == 2) {
            scanf("%d%d%d%d", &a, &c, &b, &d);
            b++, d++;
            printf("%d\n", getSum(b, d) - getSum(a, d) - getSum(b, c) + getSum(a, c));
        }
    }
}
