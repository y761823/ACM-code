////////////////////System Comment////////////////////
////Welcome to Hangzhou Dianzi University Online Judge
////http://acm.hdu.edu.cn
//////////////////////////////////////////////////////
////Username: y761823
////Nickname: Oyk
////Run ID: 
////Submit time: 2014-08-17 11:33:08
////Compiler: GUN C++
//////////////////////////////////////////////////////
////Problem ID: 1052
////Problem Title: 
////Run result: Accept
////Run time:31MS
////Run memory:332KB
//////////////////System Comment End//////////////////
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <iostream>
#include <functional>
using namespace std;

const int MAXN = 1010;

int a[MAXN], b[MAXN];
int n;

int main() {
    while(scanf("%d", &n) != EOF) {
        if(n == 0) break;
        for(int i = 0; i < n; ++i) scanf("%d", &a[i]);
        for(int i = 0; i < n; ++i) scanf("%d", &b[i]);
        sort(a, a + n, greater<int>());
        sort(b, b + n, greater<int>());

        int la = 0, ra = n - 1, lb = 0, rb = n - 1, res = 0;
        while(la <= ra) {
            while(la <= ra && a[la] > b[lb]) ++res, ++la, ++lb;
            while(la <= ra && a[ra] > b[rb]) ++res, --ra, --rb;
            if(la <= ra) res -= (a[ra] < b[lb]), --ra, ++lb;
        }
        printf("%d\n", 200 * res);
    }
}
