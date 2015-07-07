////////////////////System Comment////////////////////
////Welcome to Hangzhou Dianzi University Online Judge
////http://acm.hdu.edu.cn
//////////////////////////////////////////////////////
////Username: y761823
////Nickname: Oyk
////Run ID: 
////Submit time: 2014-01-24 17:18:15
////Compiler: GUN C++
//////////////////////////////////////////////////////
////Problem ID: 1849
////Problem Title: 
////Run result: Accept
////Run time:15MS
////Run memory:316KB
//////////////////System Comment End//////////////////
#include <cstdio>
#include <algorithm>
#include <iostream>
#include <cstring>
using namespace std;

const int MAXN = 1000;

int main() {
    int n, x;
    while(scanf("%d", &n) != EOF && n) {
        int ans = 0;
        while(n--) scanf("%d", &x), ans ^= x;
        puts(ans ? "Rabbit Win!" : "Grass Win!");
    }
}
