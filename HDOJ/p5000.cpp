////////////////////System Comment////////////////////
////Welcome to Hangzhou Dianzi University Online Judge
////http://acm.hdu.edu.cn
//////////////////////////////////////////////////////
////Username: y761823
////Nickname: Oyk
////Run ID: 
////Submit time: 2014-09-13 19:35:31
////Compiler: GUN C++
//////////////////////////////////////////////////////
////Problem ID: 5000
////Problem Title: 
////Run result: Accept
////Run time:125MS
////Run memory:24728KB
//////////////////System Comment End//////////////////
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <iostream>
#include <numeric>
#include <functional>
using namespace std;
typedef long long LL;

const int MAXN = 2010;
const int MOD = 1e9 + 7;

void update_add(int &a, int b) {
    a += b;
    if(a >= MOD) a -= MOD;
}

int a[MAXN][MAXN], sum[MAXN][MAXN];
int b[MAXN];
int n, s, T;

void solve() {
    memset(a, 0, sizeof(a));
    s = accumulate(b, b + n, 0);

    for(int i = 0; i <= b[0]; ++i) a[0][i] = 1;
    sum[0][0] = a[0][0];
    for(int j = 1; j <= s; ++j) sum[0][j] = (sum[0][j - 1] + a[0][j]) % MOD;

    for(int i = 1; i < n; ++i) {
        for(int j = 0; j <= s; ++j) {
            //for(int k = j - b[i]; k <= j; ++k) a[i][j] += a[i - 1][k];
            if(j - b[i] <= 0) a[i][j] = sum[i - 1][j];
            else a[i][j] = (sum[i - 1][j] - sum[i - 1][j - b[i] - 1] + MOD) % MOD;
        }
        sum[i][0] = a[i][0];
        for(int j = 1; j <= s; ++j) sum[i][j] = (sum[i][j - 1] + a[i][j]) % MOD;
    }
}

void print() {
    for(int j = 0; j <= s; ++j)
        printf("%4d", j);
    puts("");
    for(int i = 0; i < n; ++i) {
        for(int j = 0; j <= s; ++j)
            printf("%4d", a[i][j]);
        puts("");
    }
}

int main() {
    scanf("%d", &T);
    while(T--) {
        scanf("%d", &n);
        for(int i = 0; i < n; ++i) scanf("%d", &b[i]);
        sort(b, b + n);
        solve();
        //print();
        printf("%d\n", a[n - 1][s / 2]);
    }
}