////////////////////System Comment////////////////////
////Welcome to Hangzhou Dianzi University Online Judge
////http://acm.hdu.edu.cn
//////////////////////////////////////////////////////
////Username: y761823
////Nickname: Oyk
////Run ID: 
////Submit time: 2014-10-18 22:12:52
////Compiler: GUN C++
//////////////////////////////////////////////////////
////Problem ID: 2138
////Problem Title: 
////Run result: Accept
////Run time:140MS
////Run memory:200KB
//////////////////System Comment End//////////////////
#include <cstdio>
using namespace std;

bool isPrime(int n) {
    if(n < 2) return false;
    for(int i = 2; (long long)i * i <= n; ++i)
        if(n % i == 0) return false;
    return true;
}

int main() {
    int n;
    while(scanf("%d", &n) != EOF) {
        int ans = 0;
        for(int i = 0, a; i < n; ++i) {
            scanf("%d", &a);
            ans += isPrime(a);
        }
        printf("%d\n", ans);
    }
}