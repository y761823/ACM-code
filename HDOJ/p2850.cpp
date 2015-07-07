////////////////////System Comment////////////////////
////Welcome to Hangzhou Dianzi University Online Judge
////http://acm.hdu.edu.cn
//////////////////////////////////////////////////////
////Username: y761823
////Nickname: Oyk
////Run ID: 
////Submit time: 2014-03-16 21:08:12
////Compiler: GUN C++
//////////////////////////////////////////////////////
////Problem ID: 2850
////Problem Title: 
////Run result: Accept
////Run time:468MS
////Run memory:1500KB
//////////////////System Comment End//////////////////
#include <cstdio>
#include <algorithm>
#include <iostream>
#include <cstring>
using namespace std;

const int MAXN = 100010;

struct Node {
    int t, id;
    bool operator < (const Node &rhs) const {
        return t > rhs.t;
    }
};

Node a[MAXN];
int pos[MAXN], mach[110];
int n, m;

int main() {
    int T;
    scanf("%d", &T);
    while(T--) {
        scanf("%d%d", &n, &m);
        for(int i = 0; i < n; ++i) scanf("%d", &a[i].t), a[i].id = i;
        sort(a, a + n);
        memset(mach, 0, sizeof(mach));
        for(int i = 0; i < n; ++i) {
            int x = 0;
            for(int j = 0; j < m; ++j)
                if(mach[j] < mach[x]) x = j;
            mach[x] += a[i].t;
            pos[a[i].id] = x;
        }
        printf("%d\n%d", n, pos[0]);
        for(int i = 1; i < n; ++i) printf(" %d", pos[i]);
        puts("");
    }
}