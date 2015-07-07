////////////////////System Comment////////////////////
////Welcome to Hangzhou Dianzi University Online Judge
////http://acm.hdu.edu.cn
//////////////////////////////////////////////////////
////Username: y761823
////Nickname: Oyk
////Run ID: 
////Submit time: 2014-03-16 22:10:06
////Compiler: GUN C++
//////////////////////////////////////////////////////
////Problem ID: 4608
////Problem Title: 
////Run result: Accept
////Run time:171MS
////Run memory:416KB
//////////////////System Comment End//////////////////
#include <cstdio>
#include <iostream>
#include <algorithm>
#include <cstring>
#include <cmath>
using namespace std;
typedef long long LL;

const int MAXN = 100010;

char s[MAXN];

int main() {
    int T;
    scanf("%d", &T);
    while(T--) {
        scanf("%s", s + 1);
        int n = strlen(s + 1), sum = 0;
        for(int i = 1; i <= n; ++i) {
            sum += s[i] - '0';
        }
        bool flag = false;
        for(int i = 1; i <= 2000; ++i) {
            ++s[n];
            ++sum;
            if(s[n] == '9' + 1) {
                s[n] = '0';
                int p;
                for(p = n - 1; p > 0; --p) {
                    if(s[p] == '9') {
                        sum -= 9;
                        s[p] = '0';
                    } else break;
                }
                if(p == 0) flag = true;
                else ++s[p];
                ++sum;
            }
            if(sum % 10 == 0) break;
        }
        if(flag) putchar('1');
        printf("%s\n", s + 1);
    }
}