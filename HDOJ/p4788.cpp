////////////////////System Comment////////////////////
////Welcome to Hangzhou Dianzi University Online Judge
////http://acm.hdu.edu.cn
//////////////////////////////////////////////////////
////Username: y761823
////Nickname: Oyk
////Run ID: 
////Submit time: 2014-09-12 14:31:13
////Compiler: GUN C++
//////////////////////////////////////////////////////
////Problem ID: 4788
////Problem Title: 
////Run result: Accept
////Run time:0MS
////Run memory:320KB
//////////////////System Comment End//////////////////
#ifdef ONLINE_JUDGE
#define longformat "%lld"
#else
#define longformat "%I64d"
#endif // ONLINE_JUDGE

#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>
#include <map>
using namespace std;
typedef long long LL;

//¡°B¡±, ¡°KB¡±, ¡°MB¡±, ¡°GB¡±, ¡°TB¡±, ¡°PB¡±, ¡°EB¡±, ¡°ZB¡±, ¡°YB¡±

char s[10];
int n, T;

map<char, int> mymap;
void init() {
    mymap['B'] = 0;
    mymap['K'] = 1;
    mymap['M'] = 2;
    mymap['G'] = 3;
    mymap['T'] = 4;
    mymap['P'] = 5;
    mymap['E'] = 6;
    mymap['Z'] = 7;
    mymap['Y'] = 8;
}

double power(int p) {
    static double x = 1000.0 / 1024;
    double res = 1;
    for(int i = 0; i < p; ++i)
        res *= x;
    return res;
}

double solve() {
    double res = 1 - power(mymap[s[1]]);
    return res * 100;
}

int main() {
    init();
    scanf("%d", &T);
    for(int t = 1; t <= T; ++t) {
        scanf("%d%s", &n, s);
        printf("Case #%d: %.2f%%\n", t, solve());
    }
}
