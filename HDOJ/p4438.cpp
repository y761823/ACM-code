////////////////////System Comment////////////////////
////Welcome to Hangzhou Dianzi University Online Judge
////http://acm.hdu.edu.cn
//////////////////////////////////////////////////////
////Username: y761823
////Nickname: Oyk
////Run ID: 
////Submit time: 2013-10-03 18:14:59
////Compiler: GUN C++
//////////////////////////////////////////////////////
////Problem ID: 4438
////Problem Title: 
////Run result: Accept
////Run time:62MS
////Run memory:336KB
//////////////////System Comment End//////////////////
#include <cstdio>
#include <iostream>
#include <algorithm>
#include <cstring>
using namespace std;
typedef long long LL;

int x, y, T;
double P, Q;

int main() {
    scanf("%d", &T);
    while(T--) {
        scanf("%d%d%lf%lf", &x, &y, &P, &Q);
        double t1 = (x + y) * P;
        double t2 = t1 * Q;
        double ex1 = x * (1 - Q) + t2;
        double ex2 = y * Q + t1 - t2;
        if(ex1 > ex2) printf("tiger %.4f\n", ex1);
        else printf("wolf %.4f\n", ex2);
    }
}
