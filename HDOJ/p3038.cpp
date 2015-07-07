////////////////////System Comment////////////////////
////Welcome to Hangzhou Dianzi University Online Judge
////http://acm.hdu.edu.cn
//////////////////////////////////////////////////////
////Username: y761823
////Nickname: Oyk
////Run ID: 
////Submit time: 2014-07-22 18:08:02
////Compiler: GUN C++
//////////////////////////////////////////////////////
////Problem ID: 3038
////Problem Title: 
////Run result: Accept
////Run time:78MS
////Run memory:1516KB
//////////////////System Comment End//////////////////
#include <cstdio>
#include <iostream>
#include <algorithm>
#include <cstring>
using namespace std;
typedef long long LL;

const int MAXN = 200010;

int fa[MAXN], sum[MAXN];
int n, m;

int find_set(int x) {
    if(fa[x] == x) return x;
    int r = find_set(fa[x]);
    sum[x] += sum[fa[x]];
    return fa[x] = r;
}

int main() {
    while(scanf("%d%d", &n, &m) != EOF) {
        for(int i = 0; i <= n; ++i) fa[i] = i, sum[i] = 0;
        int ans = 0;
        for(int i = 0, x, y, z; i < m; ++i) {
            scanf("%d%d%d", &x, &y, &z);
            int fx = find_set(--x), fy = find_set(y);
            if(fx == fy) {
                ans += (sum[y] - sum[x] != z);
            } else {
                fa[fy] = fx;
                sum[fy] = sum[x] - sum[y] + z;
            }
        }
        printf("%d\n", ans);
    }
}
