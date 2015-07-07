////////////////////System Comment////////////////////
////Welcome to Hangzhou Dianzi University Online Judge
////http://acm.hdu.edu.cn
//////////////////////////////////////////////////////
////Username: y761823
////Nickname: Oyk
////Run ID: 
////Submit time: 2014-09-21 23:24:22
////Compiler: GUN C++
//////////////////////////////////////////////////////
////Problem ID: 5038
////Problem Title: 
////Run result: Accept
////Run time:296MS
////Run memory:4256KB
//////////////////System Comment End//////////////////
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
#include <cctype>
using namespace std;
typedef pair<int, int> PII;

const int MAXN = 1000010;

inline int readint() {
    char c = getchar();
    while(!isdigit(c)) c = getchar();
    int res = 0;
    while(isdigit(c)) res = res * 10 + c - '0', c = getchar();
    return res;
}

inline int sqr(int x) {
    return x * x;
}

int w[MAXN], s[MAXN];
int cnt[10010];
int mint, maxt;
int n, m, T;

int main() {
    T = readint();
    for(int t = 1; t <= T; ++t) {
        n = readint();
        for(int i = 0; i < n; ++i)
            s[i] = 10000 - sqr(100 - readint());
        memset(cnt, 0, sizeof(cnt));
        for(int i = 0; i < n; ++i)
            cnt[s[i]]++;
        maxt = -1;
        mint = n + 1;
        int v = 0;
        for(int i = 0; i <= 10000; ++i) if(cnt[i]) {
            if(maxt < cnt[i]) maxt = cnt[i];
            if(mint > cnt[i]) mint = cnt[i];
            v++;
        }
        printf("Case #%d:\n", t);
        if(v > 1 && maxt == mint) {
            puts("Bad Mushroom");
            continue;
        }
        bool flag = false;
        for(int i = 0; i <= 10000; ++i)
            if(cnt[i] == maxt) {
                if(flag) putchar(' ');
                else flag = true;
                printf("%d", i);
            }
        puts("");
    }
}