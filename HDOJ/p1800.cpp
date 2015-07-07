////////////////////System Comment////////////////////
////Welcome to Hangzhou Dianzi University Online Judge
////http://acm.hdu.edu.cn
//////////////////////////////////////////////////////
////Username: y761823
////Nickname: Oyk
////Run ID: 
////Submit time: 2014-03-16 20:21:13
////Compiler: GUN C++
//////////////////////////////////////////////////////
////Problem ID: 1800
////Problem Title: 
////Run result: Accept
////Run time:359MS
////Run memory:240KB
//////////////////System Comment End//////////////////
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

const int MAXN = 3010;

int degree[MAXN], n;

int main() {
    while(scanf("%d", &n) != EOF) {
        for(int i = 0; i < n; ++i)
            scanf("%d", degree + i);
        int ans = 1, j = n - 1;
        sort(degree, degree + n);
        for(int i = n - 2; i >= 0; --i) {
            if(degree[i] == degree[j]) ++ans;
            else --j;
        }
        printf("%d\n", ans);
    }
}