////////////////////System Comment////////////////////
////Welcome to Hangzhou Dianzi University Online Judge
////http://acm.hdu.edu.cn
//////////////////////////////////////////////////////
////Username: y761823
////Nickname: Oyk
////Run ID: 
////Submit time: 2014-01-23 23:46:50
////Compiler: GUN C++
//////////////////////////////////////////////////////
////Problem ID: 1847
////Problem Title: 
////Run result: Accept
////Run time:0MS
////Run memory:316KB
//////////////////System Comment End//////////////////
#include <cstdio>
#include <algorithm>
#include <iostream>
#include <cstring>
using namespace std;

int n;

int main() {
    while(~scanf("%d", &n)) {
        puts(n % 3 ? "Kiki" : "Cici");
    }
}
