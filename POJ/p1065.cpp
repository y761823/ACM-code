#include <cstdio>
#include <iostream>
#include <algorithm>
#include <cstring>
#include <queue>
#include <numeric>
using namespace std;
typedef long long LL;

const int MAXN = 5010;
const int INF = 0x3f3f3f3f;

pair<int, int> p[MAXN];
int g[MAXN];
int T, n;

int main() {
    scanf("%d", &T);
    while(T--) {
        scanf("%d", &n);
        for(int i = 0; i < n; ++i)
            scanf("%d%d", &p[i].first, &p[i].second);
        sort(p, p + n);
        fill(g, g + n, INF);
        for(int i = 0; i < n; ++i) {
            *lower_bound(g, g + n, -p[i].second) = -p[i].second;
        }
        printf("%d\n", lower_bound(g, g + n, INF) - g);
    }
}
