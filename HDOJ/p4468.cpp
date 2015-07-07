////////////////////System Comment////////////////////
////Welcome to Hangzhou Dianzi University Online Judge
////http://acm.hdu.edu.cn
//////////////////////////////////////////////////////
////Username: y761823
////Nickname: Oyk
////Run ID: 
////Submit time: 2014-03-16 22:00:46
////Compiler: GUN C++
//////////////////////////////////////////////////////
////Problem ID: 4468
////Problem Title: 
////Run result: Accept
////Run time:78MS
////Run memory:904KB
//////////////////System Comment End//////////////////
#include <cstdio>
#include <iostream>
#include <algorithm>
#include <cstring>
using namespace std;

const int MAXN = 100010;

char r[MAXN], s[MAXN];
int fail[MAXN];
int n;

int main() {
    int test = 0;
    while(scanf("%s", r) != EOF) {
        int n = strlen(r), m = 1, last = 1;
        memset(s, 0, sizeof(s));
        s[0] = r[0];
        for(int i = 1, j = 0; i < n; ++i) {
            while(j && r[i] != s[j]) j = fail[j];
            if(r[i] == s[j]) ++j;
            if(!j) {
                for(int k = last; k <= i; ++k) {
                    s[m] = r[k];
                    int t = fail[m];
                    while(t && s[m] != s[t]) t = fail[t];
                    fail[m + 1] = t + (s[m] == s[t]);
                    ++m;
                }
                j = m;
            }
            if(j == m) last = i + 1;
        }
        printf("Case %d: %d\n", ++test, m + n - last);
    }
}