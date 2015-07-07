////////////////////System Comment////////////////////
////Welcome to Hangzhou Dianzi University Online Judge
////http://acm.hdu.edu.cn
//////////////////////////////////////////////////////
////Username: y761823
////Nickname: Oyk
////Run ID: 
////Submit time: 2014-08-08 10:30:18
////Compiler: GUN C++
//////////////////////////////////////////////////////
////Problem ID: 4814
////Problem Title: 
////Run result: Accept
////Run time:453MS
////Run memory:324KB
//////////////////System Comment End//////////////////
#include <cstdio>
#include <iostream>
#include <cstring>
#include <algorithm>
#include <queue>
using namespace std;
typedef long long LL;

const int MAXN = 100;
const int MAXT = 2 * MAXN + 10;

struct Node {
    int __a[MAXT];
    int *a;

    Node() {
        a = __a + MAXN + 5;
    }

    void cal(int n) {
        memset(__a, 0, sizeof(__a));
        a[0] = n;
        while(true) {
            bool flag = false;
            for(int pos = -MAXN; pos <= MAXN; ++pos)
                if(a[pos] && a[pos - 1]) {
                    int t = min(a[pos], a[pos - 1]);
                    a[pos] -= t;
                    a[pos - 1] -= t;
                    a[pos + 1] += t;
                    flag = true;
                }
            for(int pos = -MAXN; pos <= MAXN; ++pos)
                if(a[pos] > 1) {
                    int t = a[pos] / 2;
                    a[pos] -= 2 * t;
                    a[pos - 2] += t;
                    a[pos + 1] += t;
                    flag = true;
                }

            if(!flag) break;
        }
    }

    void print() {
        int t = MAXN;
        while(!a[t] && t > 0) --t;
        while(t >= 0) printf("%d", a[t--]);

        t = -MAXN;
        while(!a[t] && t < 0) ++t;
        if(t != 0) {
            putchar('.');
            for(int i = -1; i >= t; --i) printf("%d", a[i]);
        }
        puts("");
    }
} G;

int main() {
    int n;
    while(scanf("%d", &n) != EOF) {
        G.cal(n);
        G.print();
    }
}
