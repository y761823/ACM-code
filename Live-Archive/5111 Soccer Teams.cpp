#include <cstdio>
#include <algorithm>
#include <cstring>
#include <iostream>
#include <set>
#include <tuple>
using namespace std;
typedef long long LL;

typedef tuple<int, int, int> Node;
#define diff(t) get<0>(t)
#define lsize(t) get<1>(t)
#define rsize(t) get<2>(t)

const int INF = 0x3f3f3f3f;

int d[10], T;
set<Node> now, nxt;

int solve() {
    now.clear();
    now.insert(Node(0, 0, 0));
    for(int i = 1; i <= 9; ++i) {
        nxt.clear();
        for(auto &t : now) {
            for(int k = 0; k <= d[i]; ++k)
                nxt.insert(Node(diff(t) + (2 * k - d[i]) * i,
                                lsize(t) + k,
                                rsize(t) + d[i] - k));
        }
        now.swap(nxt);
    }

    int res = INF;
    for(auto &t : now) if(diff(t) % 11 == 0)
        res = min(res, lsize(t) == rsize(t) ? lsize(t) * 2 : max(lsize(t), rsize(t)) * 2 - 1);
    return res == INF ? -1 : res;
}

int main() {
    scanf("%d", &T);
    while(T--) {
        for(int i = 1; i <= 9; ++i) scanf("%d", &d[i]);
        printf("%d\n", solve());
    }
}