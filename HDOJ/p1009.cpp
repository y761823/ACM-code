////////////////////System Comment////////////////////
////Welcome to Hangzhou Dianzi University Online Judge
////http://acm.hdu.edu.cn
//////////////////////////////////////////////////////
////Username: y761823
////Nickname: Oyk
////Run ID: 
////Submit time: 2014-11-07 10:57:05
////Compiler: GUN C++
//////////////////////////////////////////////////////
////Problem ID: 1009
////Problem Title: 
////Run result: Accept
////Run time:31MS
////Run memory:312KB
//////////////////System Comment End//////////////////
#include <cstdio>
#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;

struct Node {
    int J, F;
    Node() {}
    Node(int j, int f): J(j), F(f) {}
    bool operator < (const Node &rhs) const {
        return J * rhs.F > F * rhs.J;//J / F < rhs.J / rhs.F;
    }
};

Node a[1010];

int main() {
    int n, m;
    while(scanf("%d%d", &m, &n) != EOF) {
        if(n == -1 && m == -1) break;
        for(int i = 0; i < n; ++i) scanf("%d%d", &a[i].J, &a[i].F);
        sort(a, a + n);
        double ans = 0;
        for(int i = 0; i < n; ++i) {
            if(m >= a[i].F) {
                ans += a[i].J;
                m -= a[i].F;
            }
            else {
                ans += a[i].J * double(m) / a[i].F;
                break;
            }
        }
        printf("%.3f\n", ans);
    }
}