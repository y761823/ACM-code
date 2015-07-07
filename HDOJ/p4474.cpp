////////////////////System Comment////////////////////
////Welcome to Hangzhou Dianzi University Online Judge
////http://acm.hdu.edu.cn
//////////////////////////////////////////////////////
////Username: y761823
////Nickname: Oyk
////Run ID: 
////Submit time: 2014-03-16 21:58:09
////Compiler: GUN C++
//////////////////////////////////////////////////////
////Problem ID: 4474
////Problem Title: 
////Run result: Accept
////Run time:312MS
////Run memory:688KB
//////////////////System Comment End//////////////////
#include <cstdio>
#include <cstring>
#include <queue>
#include <algorithm>
#include <cstring>
using namespace std;

const int MAXN = 10010;

int pre[MAXN], val[MAXN];
bool vis[MAXN], exist[12];
int n, m;

void init() {
    memset(vis, 0, sizeof(vis));
    memset(pre, 0, sizeof(pre));
    memset(exist, 0, sizeof(exist));
}

void print(int t) {
    if(pre[t]) print(pre[t]);
    printf("%d", val[t]);
}

void solve() {
    queue<int> que; que.push(0);
    while(!que.empty()) {
        int x = que.front(); que.pop();
        int beg = (x == 0);
        for(int i = beg; i < 10; ++i) {
            if(exist[i]) continue;
            int t = (x * 10 + i) % n;
            if(vis[t]) continue;
            vis[t] = true;
            pre[t] = x;
            val[t] = i;
            if(t == 0) {
                print(t);
                puts("");
                return ;
            }
            que.push(t);
        }
    }
    puts("-1");
}

int main() {
    int t = 0;
    while(scanf("%d%d", &n, &m) != EOF) {
        init();
        while(m--) {
            int x;
            scanf("%d", &x);
            exist[x] = true;
        }
        printf("Case %d: ", ++t);
        solve();
    }
}