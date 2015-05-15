#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
#define FOR(i, n) for(int i = 0; i < n; ++i)

LL calc(LL k) {
    if(k == 0) return 1;
    return ((k + 1) << (k + 1)) - 1;
}

int main() {
    LL n, ans = 0;
    scanf("%I64d", &n);
    while(calc(ans) < n) ans++;
    cout<<ans<<endl;
}
