////////////////////System Comment////////////////////
////Welcome to Hangzhou Dianzi University Online Judge
////http://acm.hdu.edu.cn
//////////////////////////////////////////////////////
////Username: y761823
////Nickname: Oyk
////Run ID: 
////Submit time: 2014-03-16 21:12:57
////Compiler: GUN C++
//////////////////////////////////////////////////////
////Problem ID: 3699
////Problem Title: 
////Run result: Accept
////Run time:15MS
////Run memory:320KB
//////////////////System Comment End//////////////////
#include <cstdio>
#include <iostream>
#include <cstring>
#include <algorithm>
using namespace std;

const int MAXN = 12;

char s1[MAXN], s2[MAXN], s3[MAXN];
int trans[MAXN];
bool exist[MAXN], use[MAXN];
int ans;

int s_to_i(char *s) {
    if(trans[s[0] - 'A'] == 0 && s[1]) return -1;
    int ret = 0;
    for(int i = 0; s[i]; ++i)
        ret = ret * 10 + trans[s[i] - 'A'];
    return ret;
}

void dfs(int dep) {
    if(dep == 5) {
        int a1 = s_to_i(s1), a2 = s_to_i(s2), a3 = s_to_i(s3);
        if(a1 == -1 || a2 == -1 || a3 == -1) return ;
        if(a1 + a2 == a3) ++ans;
        if(a1 - a2 == a3) ++ans;
        if(a1 * a2 == a3) ++ans;
        if(a2 && a1 == a2 * a3) ++ans;
        return ;
    }
    if(!exist[dep]) {
        dfs(dep + 1);
        return ;
    }
    for(int i = 0; i <= 9; ++i) {
        if(use[i]) continue;
        trans[dep] = i;
        use[i] = true;
        dfs(dep + 1);
        use[i] = false;
    }
}

void check(char *s) {
    for(int i = 0; s[i]; ++i)
        exist[s[i] - 'A'] = true;
}

int main() {
    int T;
    scanf("%d", &T);
    while(T--) {
        scanf("%s%s%s", s1, s2, s3);
        memset(exist, 0, sizeof(exist));
        check(s1), check(s2), check(s3);
        ans = 0;
        dfs(0);
        printf("%d\n", ans);
    }
}