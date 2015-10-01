#include <cstdio>
#include <cstring>
#include <algorithm>
#include <iostream>
using namespace std;
typedef long long LL;

const int MAXN = 100010;

LL sum[MAXN];
int n, m, k;

LL solve() {
    for(int i = 1; i <= m; ++i)
        sum[i] = sum[i - 1] + (m - i + 1);

    LL res = 0;
    for(int i = 1; i <= n; ++i) {
        int l = min(m, (k - 2 * i) / 2);
        if(l <= 0) break;
        res += (n - i + 1) * sum[l];
    }
    return res;
}

int main() {
    while(scanf("%d%d%d", &n, &m, &k) != EOF) {
        cout<<solve()<<endl;
    }
}
