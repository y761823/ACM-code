////////////////////System Comment////////////////////
////Welcome to Hangzhou Dianzi University Online Judge
////http://acm.hdu.edu.cn
//////////////////////////////////////////////////////
////Username: y761823
////Nickname: Oyk
////Run ID: 
////Submit time: 2014-03-16 22:09:34
////Compiler: GUN C++
//////////////////////////////////////////////////////
////Problem ID: 4602
////Problem Title: 
////Run result: Accept
////Run time:93MS
////Run memory:364KB
//////////////////System Comment End//////////////////
#include <cstdio>
#include <iostream>
#include <algorithm>
#include <cstring>
#include <cmath>
using namespace std;
typedef long long LL;

const int MAXN = 100010;
const int MAXE = 200010;
const int INF = 0x7fffffff;
const int MOD = 1000000007;

int n, k;
int cnt;

void dfs(int x, int sum) {
    if(x == 0) cnt += sum;
    for(int i = 1; i <= x; ++i) {
        dfs(x - i, sum + (i == k));
    }
}

LL mul(LL x, int p) {
    if(p < 0) return 0;
    LL ret = 1;
    while(p) {
        if(p & 1) ret = (ret * x) % MOD;
        x = (x * x) % MOD;
        p >>= 1;
    }
    return ret;
}

int main() {
    int T;
    scanf("%d", &T);
    while(T--) {
        scanf("%d%d", &n, &k);
        int t = n - k + 1;
        cout<<(((t - 2) * mul(2, t - 3) + mul(2, t - 1)) % MOD)<<endl;
    }
}