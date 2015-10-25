#include <cstdio>
#include <iostream>
#include <algorithm>
#include <cstring>
#include <queue>
using namespace std;
typedef long long LL;

const int MAXN = 10010;

struct Oil {
    int a, b;
    void read() {
        scanf("%d%d", &a, &b);
    }
    bool operator < (const Oil &rhs) const {
        return a > rhs.a;
    }
} oil[MAXN];

priority_queue<int> que;
int n, l, p;

int solve() {
    sort(oil, oil + n);
    int res = 0;
    for(int i = 0; i <= n; ++i) {
        while(l - oil[i].a > p) {
            if(que.empty()) return -1;
            res++;
            p += que.top(); que.pop();
        }
        p -= l - oil[i].a;
        l = oil[i].a;
        que.push(oil[i].b);
    }
    return res;
}

int main() {
    scanf("%d", &n);
    for(int i = 0; i < n; ++i)
        oil[i].read();
    scanf("%d%d", &l, &p);
    printf("%d\n", solve());
}
