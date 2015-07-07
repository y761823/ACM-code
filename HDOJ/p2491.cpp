////////////////////System Comment////////////////////
////Welcome to Hangzhou Dianzi University Online Judge
////http://acm.hdu.edu.cn
//////////////////////////////////////////////////////
////Username: y761823
////Nickname: Oyk
////Run ID: 
////Submit time: 2014-03-16 21:02:35
////Compiler: GUN C++
//////////////////////////////////////////////////////
////Problem ID: 2491
////Problem Title: 
////Run result: Accept
////Run time:343MS
////Run memory:1104KB
//////////////////System Comment End//////////////////
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;

const int MAXN = 100010;
const int INF = 0x3fff3fff;

struct Node {
    int s, t;
    bool operator < (const Node &rhs) const {
        return s - rhs.s < rhs.t - t;//(s + t) < (rhs.s + rhs.t);
    }
} wed[MAXN];

int n;

bool solve() {
    sort(wed, wed + n);
    int last = 0;
    for(int i = 0; i < n; ++i) {
        int len = (wed[i].t - wed[i].s) / 2 + 1;
        if(last + len > wed[i].t) return false;
        last = max(last, wed[i].s) + len;
    }
    return true;
}

int main() {
    while(scanf("%d", &n) != EOF) {
        if(n == 0) break;
        for(int i = 0; i < n; ++i) scanf("%d%d", &wed[i].s, &wed[i].t);
        if(solve()) puts("YES");
        else puts("NO");
    }
}