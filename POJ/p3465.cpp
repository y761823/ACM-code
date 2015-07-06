#include <cstdio>
#include <algorithm>
#include <cstring>
#include <iostream>
#include <queue>
using namespace std;
typedef long long LL;

const int MAXN = 100010;

int a[MAXN];
int n, x, y, h1, h2;
int k, ans;

bool solve() {
    priority_queue<int> que;
    int hh = h2;
    for(int i = 1; i <= n; ++i) {
        h1 -= a[i];
        h2 -= x;
        ans = max(ans, hh - h2);
        if(h2 <= 0) {
            ans = i;
            return true;
        }
        que.push(max(a[i], y));
        if(h1 <= 0) {
            h1 += que.top(); que.pop();
            h2 += x;
        }
    }
    return false;
}

int main() {
    scanf("%d%d%d%d%d", &n, &x, &y, &h1, &h2);
    for(int i = 1; i <= n; ++i) scanf("%d", &a[i]);
    if(solve()) printf("Win\n%d\n", ans);
    else printf("Lose\n%d\n", ans);
}
