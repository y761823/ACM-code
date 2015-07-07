////////////////////System Comment////////////////////
////Welcome to Hangzhou Dianzi University Online Judge
////http://acm.hdu.edu.cn
//////////////////////////////////////////////////////
////Username: y761823
////Nickname: Oyk
////Run ID: 
////Submit time: 2014-08-12 17:38:02
////Compiler: GUN C++
//////////////////////////////////////////////////////
////Problem ID: 4574
////Problem Title: 
////Run result: Accept
////Run time:421MS
////Run memory:316KB
//////////////////System Comment End//////////////////
#include <cstdio>
#include <algorithm>
#include <iostream>
#include <cstring>
using namespace std;
typedef long long LL;

const int MAXN = 1000010;
const int INF = 0x7fff7fff;

int ans[50], res;
int a, b, l, r, k, T;
int maxdep;

int power(int x, int p) {
    LL res = 1;
    for(int i = 1; i <= p; ++i) {
        res *= x;
        if(res > INF) return INF;
    }
    return (int)res;
}

int dfs(int a, int b, int l, int r, int k, int dep) {
    if(l > r) return 0;
    if(dep == maxdep) {
        int t = max(0, min(r, b) - max(l, a) + 1);
        ans[dep] = max(l, a) + k - 1;
        return t;
    }
    int st = max(a, (l - 1) / power(b, maxdep - dep) + 1);
    int ed = min(b, r / power(a, maxdep - dep));
    //cout<<st<<" "<<ed<<endl;
    int res = 0;
    for(int i = st; i <= ed && LL(i) * i <= r; ++i) {
        ans[dep] = i;
        res += dfs(i, b, (l - 1) / i + 1, r / i, k - res, dep + 1);
        if(res >= k) break;
    }
    return res;
}

void solve() {
    for(maxdep = 1; maxdep <= 30; ++maxdep) {
        int t = dfs(a, b, l, r, k, 1);
        k -= t;
        if(k <= 0) break;
    }
    if(maxdep == 31) res = -1;
    else {
        res = 1;
        for(int i = 1; i <= maxdep; ++i) res *= ans[i];
    }
}

int main() {
    scanf("%d", &T);
    for(int t = 1; t <= T; ++t) {
        scanf("%d%d%d%d%d", &a, &b, &l, &r, &k);
        solve();
        printf("Case #%d: %d\n", t, res);
        if(res != -1) {
            for(int i = 1; i < maxdep; ++i) printf("%d ", ans[i]);
            printf("%d\n", ans[maxdep]);
        }
    }
}
