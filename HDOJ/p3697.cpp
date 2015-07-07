////////////////////System Comment////////////////////
////Welcome to Hangzhou Dianzi University Online Judge
////http://acm.hdu.edu.cn
//////////////////////////////////////////////////////
////Username: y761823
////Nickname: Oyk
////Run ID: 
////Submit time: 2014-03-16 21:13:32
////Compiler: GUN C++
//////////////////////////////////////////////////////
////Problem ID: 3697
////Problem Title: 
////Run result: Accept
////Run time:31MS
////Run memory:324KB
//////////////////System Comment End//////////////////
#include <cstdio>
#include <iostream>
#include <cstring>
#include <algorithm>
using namespace std;

const int MAXN = 310;

int a[MAXN], b[MAXN];
bool sel[MAXN];
int n;

int solve() {
    int ret = 0;
    for(int st = 0; st < 5; ++st) {
        memset(sel, 0, sizeof(sel));
        int ans = 0;
        for(int i = st; i <= 1000; i += 5) {
            int best = -1;
            for(int j = 0; j < n; ++j)
                if(!sel[j] && a[j] <= i && i < b[j]) {
                    if(best == -1) best = j;
                    else if(b[j] < b[best]) best = j;
                }
            if(best != -1) {
                sel[best] = true;
                ++ans;
            }
        }
        if(ret < ans) ret = ans;
    }
    return ret;
}

int main() {
    while(scanf("%d", &n) != EOF && n) {
        for(int i = 0; i < n; ++i) scanf("%d%d", &a[i], &b[i]);
        printf("%d\n", solve());
    }
}