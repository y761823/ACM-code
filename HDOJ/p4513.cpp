////////////////////System Comment////////////////////
////Welcome to Hangzhou Dianzi University Online Judge
////http://acm.hdu.edu.cn
//////////////////////////////////////////////////////
////Username: y761823
////Nickname: Oyk
////Run ID: 
////Submit time: 2014-05-02 16:19:02
////Compiler: GUN C++
//////////////////////////////////////////////////////
////Problem ID: 4513
////Problem Title: 
////Run result: Accept
////Run time:421MS
////Run memory:1872KB
//////////////////System Comment End//////////////////
#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

const int MAXN = 100010;

int p[MAXN << 1], s[MAXN << 1];
int n, cnt, T;

void manacher() {
    int mx = 0, id;
    for(int i = 1; i < cnt; ++i) {
        if(mx > i) p[i] = min(p[2 * id - i], mx - i);
        else p[i] = 1;
        while(s[i + p[i]] == s[i - p[i]] && s[i + p[i]] <= s[i + p[i] - 2]) ++p[i];
        if(i + p[i] > mx) {
            id = i;
            mx = i + p[i];
        }
    }
}

int main() {
    scanf("%d", &T);
    while(T--) {
        scanf("%d", &n);
        cnt = 0;
        s[cnt++] = -2; s[cnt++] = -1;
        for(int i = 0; i < n; ++i) {
            scanf("%d", &s[cnt++]);
            s[cnt++] = -1;
        }
        s[cnt] = 0;
        manacher();
        int ans = 0;
        for(int i = 0; i < cnt; ++i)
            ans = max(ans, p[i] - 1);
        printf("%d\n", ans);
    }
}
