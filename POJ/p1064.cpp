#include <cstdio>
#include <iostream>
#include <algorithm>
#include <cstring>
#include <cmath>
#include <numeric>
using namespace std;
typedef long long LL;

const int MAXN = 10010;
const int INF = 0x3f3f3f3f;

int len[MAXN];
int n, k;

bool check(int x) {
    int cnt = 0;
    for(int i = 0; i < n && cnt < k; ++i)
        cnt += len[i] / x;
    return cnt >= k;
}

int main() {
    scanf("%d%d", &n, &k);
    for(int i = 0, a, b; i < n; ++i) {
        scanf("%d.%d", &a, &b);
        len[i] = a * 100 + b;
    };
    int l = 1, r = *max_element(len, len + n) + 1;
    while(l < r) {
        int mid = (l + r) >> 1;
        if(check(mid)) l = mid + 1;
        else r = mid;
    }
    printf("%d.%02d\n", (l - 1) / 100, (l - 1) % 100);
}
