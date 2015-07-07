////////////////////System Comment////////////////////
////Welcome to Hangzhou Dianzi University Online Judge
////http://acm.hdu.edu.cn
//////////////////////////////////////////////////////
////Username: y761823
////Nickname: Oyk
////Run ID: 
////Submit time: 2014-05-25 20:03:33
////Compiler: GUN C++
//////////////////////////////////////////////////////
////Problem ID: 4831
////Problem Title: 
////Run result: Accept
////Run time:593MS
////Run memory:488KB
//////////////////System Comment End//////////////////
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <iostream>
using namespace std;
typedef long long LL;

const int MAXN = 10010;

int x[MAXN], val[MAXN];
int well[MAXN], cnt;
int n1[MAXN], n2[MAXN];
int T, n, k;

int main() {
    scanf("%d", &T);
    for(int t = 1; t <= T; ++t) {
        scanf("%d", &n);
        for(int i = 0; i < n; ++i) scanf("%d%d", &x[i], &val[i]);

        cnt = 0;
        for(int i = 0; i < n; ++i)
            if(val[i]) well[cnt++] = i;
        memset(n1, -1, n * sizeof(int));
        memset(n2, -1, n * sizeof(int));

        if(cnt) for(int i = 0; i < well[0]; ++i) n1[i] = well[0];
        for(int i = 0; i < cnt - 1; ++i) {
            int pre = well[i], nxt = well[i + 1];
            for(int j = pre + 1; j < nxt; ++j) {
                if(x[j] - x[pre] < x[nxt] - x[j]) {
                    n1[j] = pre;
                } else if(x[j] - x[pre] > x[nxt] - x[j]) {
                    n1[j] = nxt;
                } else {
                    n1[j] = pre;
                    n2[j] = nxt;
                }
            }
        }
        if(cnt) for(int i = well[cnt - 1] + 1; i < n; ++i) n1[i] = well[cnt - 1];

        scanf("%d", &k);
        printf("Case #%d:\n", t);
        while(k--) {
            char c;
            int a, b;
            scanf(" %c", &c);
            if(c == 'U') {
                scanf("%d%d", &a, &b);
                val[a] = b;
            } else {
                scanf("%d", &a);
                int ans = 0;
                for(int i = 0; i < n; ++i) {
                    if(val[i]) ans += (val[i] <= a);
                    else {
                        int tmp = -1;
                        if(n1[i] != -1) tmp = max(tmp, val[n1[i]]);
                        if(n2[i] != -1) tmp = max(tmp, val[n2[i]]);
                        ans += (tmp != -1 && tmp <= a);
                    }
                }
                printf("%d\n", ans);
            }
        }
    }
}
