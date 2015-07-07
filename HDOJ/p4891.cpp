////////////////////System Comment////////////////////
////Welcome to Hangzhou Dianzi University Online Judge
////http://acm.hdu.edu.cn
//////////////////////////////////////////////////////
////Username: y761823
////Nickname: Oyk
////Run ID: 
////Submit time: 2014-08-05 20:52:35
////Compiler: GUN C++
//////////////////////////////////////////////////////
////Problem ID: 4891
////Problem Title: 
////Run result: Accept
////Run time:15MS
////Run memory:676KB
//////////////////System Comment End//////////////////
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;
typedef long long LL;

const int MAXN = 1048576;
const int INF = 100000;

char s[MAXN];
int n;

void update(int &a, LL b) {
    if(a == -1) return;
    if(a * b > INF) a = -1;
    else a *= b;
}

int solve(int n) {
    int ans = 1;
    for(int i = 0; i < n && ans != -1; ++i) {
        if(s[i] == '{') {
            int cnt = 0;
            while(i < n && s[i] != '}') cnt += (s[i++] == '|');
            update(ans, cnt + 1);
        }
        if(s[i] == '$') {
            ++i;
            while(true) {
                while(s[i] != '$' && s[i] != ' ') ++i;
                if(s[i] == '$') break;
                int cnt = 0;
                while(s[i] == ' ') ++cnt, ++i;
                update(ans, cnt + 1);
            }
        }
    }
    return ans;
}

int main() {
    while(scanf("%d", &n) != EOF) {
        int p = 0;
        getchar();
        for(int i = 0; i < n; ++i) {
            gets(s + p);
            p += strlen(s + p) + 1;
        }
        int res = solve(p - 1);
        if(res == -1) puts("doge");
        else printf("%d\n", res);
    }
}
