/*
ID: y7618231
PROG: theme
LANG: C++11
*/
#ifdef OYK_JUDGE
#define longformat "%I64d"
#else
#define longformat "%lld"
#endif // OYK_JUDGE

#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>
#include <numeric>
#include <set>
using namespace std;
typedef long long LL;
#define REP(i, n) for(int i = 0; i < n; ++i)
#define FOR(i, s, t) for(int i = s; i <= t; ++i)

const int MAXN = 5010;
const int seed = 313;
const int MOD = 1000000007;

set<int> st;
int a[MAXN], myhash[MAXN];
int n;

int solve() {
    memcpy(myhash, a, n * sizeof(int));
    int k;
    for(k = 2; k < n; ++k) {
        bool flag = false;
        st.clear();
        for(int i = k; !flag && i + k - 1 < n; ++i) {
            st.insert(myhash[i - k]);
            if(st.find(myhash[i]) != st.end()) flag = true;
        }
        if(!flag) break;
        for(int i = 0; i + k < n; ++i) {
            myhash[i] = ((LL)myhash[i] * seed + a[i + k - 1]) % MOD;
        }
    }
    k--;
    return k < 5 ? 0 : k;
}

int main() {
#ifndef OYK_JUDGE
    freopen("theme.in", "r", stdin); freopen("theme.out", "w", stdout);
#endif // OYK_JUDGE
    scanf("%d", &n);
    for(int i = 0; i < n; ++i) scanf("%d", &a[i]);
    for(int i = 0; i < n - 1; ++i)
        a[i] = a[i + 1] - a[i] + 100;
    printf("%d\n", solve());
}
