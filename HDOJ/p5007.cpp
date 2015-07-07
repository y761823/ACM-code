////////////////////System Comment////////////////////
////Welcome to Hangzhou Dianzi University Online Judge
////http://acm.hdu.edu.cn
//////////////////////////////////////////////////////
////Username: y761823
////Nickname: Oyk
////Run ID: 
////Submit time: 2014-09-14 18:36:31
////Compiler: GUN C++
//////////////////////////////////////////////////////
////Problem ID: 5007
////Problem Title: 
////Run result: Accept
////Run time:15MS
////Run memory:312KB
//////////////////System Comment End//////////////////
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <iostream>
#include <queue>
using namespace std;
typedef long long LL;

const int MAXN = 100010;

char s1[4][10] = {"Apple", "iPhone", "iPod", "iPad"};
int len1[4] = {5, 5, 4, 4};
char s2[] = "Sony";
int len2 = 4;
char ans[2][20] = {"MAI MAI MAI!", "SONY DAFA IS GOOD!"};
char s[MAXN];

void solve(char str[]) {
    for(int i = 0; i < 4; ++i) {
        if(strncmp(str, s1[i], len1[i]) == 0) {
            puts(ans[0]);
            return ;
        }
    }
    if(strncmp(str, s2, len2) == 0)
        puts(ans[1]);
}

int main() {
    while(scanf("%s", s) != EOF) {
        int n = strlen(s);
        for(int i = 0; i < n; ++i)
            solve(s + i);
    }
}