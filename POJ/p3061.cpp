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

int val[MAXN];
int T, n, s;

int main() {
    scanf("%d", &T);
    while(T--) {
        scanf("%d%d", &n, &s);
        for(int i = 0; i < n; ++i)
            scanf("%d", &val[i]);
        int l = 0, sum = 0, res = INF;
        for(int r = 0; r < n; ++r) {
            sum += val[r];
            while(l < r && sum - val[l] >= s) sum -= val[l++];
            if(sum >= s) res = min(res, r - l + 1);
        }
        if(res == INF) res = 0;
        printf("%d\n", res);
    }
}
