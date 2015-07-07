////////////////////System Comment////////////////////
////Welcome to Hangzhou Dianzi University Online Judge
////http://acm.hdu.edu.cn
//////////////////////////////////////////////////////
////Username: y761823
////Nickname: Oyk
////Run ID: 
////Submit time: 2013-10-03 15:35:10
////Compiler: GUN C++
//////////////////////////////////////////////////////
////Problem ID: 4432
////Problem Title: 
////Run result: Accept
////Run time:0MS
////Run memory:348KB
//////////////////System Comment End//////////////////
#include <cstdio>
#include <iostream>
#include <algorithm>
#include <cstring>
#include <cmath>
#include <vector>
using namespace std;
typedef long long LL;

const int MAXN = 100010;

int n, m;
char op[] = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'A', 'B', 'C', 'D', 'E', 'F'};

vector<char> vec;

void print(LL ans) {
    //cout<<ans<<endl;
    vec.clear();
    if(ans == 0) vec.push_back('0');
    while(ans) {
        vec.push_back(op[ans % m]);
        ans /= m;
    }
    for(int i = vec.size() - 1; i >= 0; --i) putchar(vec[i]);
    printf("\n");
}

LL calc(int x) {
    LL ret = 0;
    while(x) {
        int t = x % m;
        ret += t * t;
        x /= m;
    }
    return ret;
}

void solve() {
    int MAX = sqrt(n + 0.5);
    long long ans = 0;
    for(int i = 1; i <= MAX; ++i) {
        if(n % i == 0) {
            ans += calc(i);
            if(i * i != n) ans += calc(n / i);
        }
    }
    print(ans);
}

int main() {
    while(scanf("%d%d", &n, &m) != EOF)
        solve();
}
