#include <cstdio>
#include <iostream>
#include <algorithm>
#include <cstring>
#include <cmath>
#include <numeric>
using namespace std;
typedef long long LL;

const int MAXN = 100010;
const int INF = 0x3f3f3f3f;

int pos[MAXN];
int n, m;

bool check(int dis) {
    int cnt = 0, last = -INF;
    for(int i = 0; i < n; ++i) {
        if(pos[i] - last >= dis) {
            cnt++;
            last = pos[i];
        }
    }
    return cnt >= m;
}

int main() {
    scanf("%d%d", &n, &m);
    for(int i = 0; i < n; ++i)
        scanf("%d", &pos[i]);
    sort(pos, pos + n);
    int l = 1, r = pos[n - 1] - pos[0] + 1;
    while(l < r) {
        int mid = (l + r) >> 1;
        if(check(mid)) l = mid + 1;
        else r = mid;
    }
    printf("%d\n", l - 1);
}
