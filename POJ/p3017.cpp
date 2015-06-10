#include <cstdio>
#include <cstring>
#include <algorithm>
#include <iostream>
#include <set>
using namespace std;
typedef long long LL;

const int MAXN = 100010;

multiset<LL> st;
int a[MAXN];
int que[MAXN], l, r;
int n;
LL dp[MAXN], m;

LL solve() {
    if(*max_element(a + 1, a + n + 1) > m) return -1;
    LL sum = 0;
    int low = 1;
    for(int i = 1; i <= n; ++i) {
        sum += a[i];
        while(sum > m) sum -= a[low++];

        while(l != r && que[l] < low) {
            if(r - l > 1) st.erase(dp[que[l]] + a[que[l + 1]]);
            l++;
        }
        while(l != r && a[que[r - 1]] <= a[i]) {
            if(r - l > 1) st.erase(dp[que[r - 2]] + a[que[r - 1]]);
            r--;
        }
        que[r++] = i;
        if(r - l > 1) st.insert(dp[que[r - 2]] + a[i]);

        dp[i] = dp[low - 1] + a[que[l]];
        if(r - l > 1) dp[i] = min(dp[i], *st.begin());
    }
    return dp[n];
}

int main() {
    scanf("%d%I64d", &n, &m);
    for(int i = 1; i <= n; ++i) scanf("%d", &a[i]);
    printf("%I64d\n", solve());
}
