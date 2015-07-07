////////////////////System Comment////////////////////
////Welcome to Hangzhou Dianzi University Online Judge
////http://acm.hdu.edu.cn
//////////////////////////////////////////////////////
////Username: y761823
////Nickname: Oyk
////Run ID: 
////Submit time: 2014-01-24 00:06:05
////Compiler: GUN C++
//////////////////////////////////////////////////////
////Problem ID: 1848
////Problem Title: 
////Run result: Accept
////Run time:0MS
////Run memory:348KB
//////////////////System Comment End//////////////////
#include <cstdio>
#include <algorithm>
#include <iostream>
#include <cstring>
#include <vector>
using namespace std;

const int MAXN = 1000;

int fib[MAXN], cnt;
int m, n, p;
int sg[MAXN + 10];

void build_fibonacci() {
    fib[0] = 1; fib[1] = 2;
    cnt = 2;
    while(fib[cnt - 1] <= MAXN) {
        fib[cnt] = fib[cnt - 1] + fib[cnt - 2];
        ++cnt;
    }
}

void build_sg() {
    vector<int> g;
    for(int i = 1; i <= MAXN; ++i) {
        g.clear();
        for(int j = 0; i - fib[j] >= 0; ++j) {
            g.push_back(sg[i - fib[j]]);
        }
        sort(g.begin(), g.end());
        int n = unique(g.begin(), g.end()) - g.begin();
        for(int j = 0; j < n; ++j) {
            if(sg[i] == g[j]) ++sg[i];
            else break;
        }
    }
}

int main() {
    build_fibonacci();
    build_sg();
    while(~scanf("%d%d%d", &m, &n, &p)) {
        if(m == 0 && n == 0 && p == 0) break;
        puts((sg[m] ^ sg[n] ^ sg[p]) ? "Fibo" : "Nacci");
    }
}
