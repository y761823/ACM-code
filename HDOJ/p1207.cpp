////////////////////System Comment////////////////////
////Welcome to Hangzhou Dianzi University Online Judge
////http://acm.hdu.edu.cn
//////////////////////////////////////////////////////
////Username: y761823
////Nickname: Oyk
////Run ID: 
////Submit time: 2014-03-16 21:09:16
////Compiler: GUN C++
//////////////////////////////////////////////////////
////Problem ID: 1207
////Problem Title: 
////Run result: Accept
////Run time:62MS
////Run memory:368KB
//////////////////System Comment End//////////////////
#include <cstdio>
#include <algorithm>
#include <cstring>
#include <cmath>
#include <iostream>
using namespace std;
typedef unsigned long long LL;

const int MAXN = 66;
LL ans[MAXN];

LL power(int x, int p) {
    LL ret = 1;
    for(int i = 0; i < p; ++i) ret *= x;
    return ret;
}

int main() {
    ans[1] = 1;
    ans[2] = 3;
    ans[3] = 5;
    //ans[4] = 9;
    //ans[5] = 13;
    //for(int i = 4; i <= 64; ++i) ans[i] = 2 * ans[i - 2] + 3;
    for(int i = 4; i <= 64; ++i) {
        LL tmp = 0x7fff7fff7fff7fffLL;
        for(int j = 1; j < i; ++j) {
            tmp = min(tmp, 2 * (ans[j] + power(2, i - j - 1) - 1) + 1);
            //cout<<i<<' '<<j<<endl;
            //cout<<2 * (ans[j] + (int)pow(2, i - j - 1) - 1) + 1<<endl;
        }
        ans[i] = tmp;
    }
    //for(int i = 4; i <= 64; ++i) cout<<i<<' '<<ans[i]<<endl;
    int n;
    while(scanf("%d", &n) != EOF) {
        cout<<ans[n]<<endl;
    }
}