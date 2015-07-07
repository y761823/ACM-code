////////////////////System Comment////////////////////
////Welcome to Hangzhou Dianzi University Online Judge
////http://acm.hdu.edu.cn
//////////////////////////////////////////////////////
////Username: y761823
////Nickname: Oyk
////Run ID: 
////Submit time: 2014-08-28 00:04:47
////Compiler: GUN C++
//////////////////////////////////////////////////////
////Problem ID: 4028
////Problem Title: 
////Run result: Accept
////Run time:296MS
////Run memory:11804KB
//////////////////System Comment End//////////////////
#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>
#include <cmath>
#include <set>
#include <map>
using namespace std;
typedef long long LL;
typedef long double LDB;

const int MAXN = 55;
const int INF = 0x3f3f3f3f;

LL lcm(LL a, LL b) {
    return a / __gcd(a, b) * b;
}

map<LL, LL> cnt[MAXN];

void make(int i) {
    cnt[i][i]++;
    for(map<LL, LL>::iterator it = cnt[i - 1].begin(); it != cnt[i - 1].end(); ++it)
        cnt[i][lcm(it->first, i)] += it->second;
}

int main() {
    cnt[1][1] = 1;
    for(int i = 2; i <= 40; ++i) {
        cnt[i] = cnt[i - 1];
        make(i);
        //cout<<i<<" "<<cnt[i].size()<<endl;
    }
    int T, n;
    LL m;
    scanf("%d", &T);
    for(int t = 1; t <= T; ++t) {
        scanf("%d%I64d", &n, &m);
        LL res = 0;
        for(map<LL, LL>::iterator it = cnt[n].begin(); it != cnt[n].end(); ++it) {
            if(it->first >= m) res += it->second;
        }
        printf("Case #%d: %I64d\n", t, res);
    }
}