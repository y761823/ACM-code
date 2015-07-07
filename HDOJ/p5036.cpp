////////////////////System Comment////////////////////
////Welcome to Hangzhou Dianzi University Online Judge
////http://acm.hdu.edu.cn
//////////////////////////////////////////////////////
////Username: y761823
////Nickname: Oyk
////Run ID: 
////Submit time: 2014-09-25 16:11:23
////Compiler: GUN C++
//////////////////////////////////////////////////////
////Problem ID: 5036
////Problem Title: 
////Run result: Accept
////Run time:1640MS
////Run memory:420KB
//////////////////System Comment End//////////////////
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
#include <bitset>
using namespace std;
typedef pair<int, int> PII;

const int MAXV = 1010;
const int MAXE = MAXV * MAXV;

bitset<MAXV> mat[MAXV];
int n, T;

void init() {
    for(int i = 1; i <= n; ++i) {
        mat[i].reset();
        mat[i].set(i);
    }
}

#define FOR(i, n) for(int i = 1; i <= n; ++i)
double solve() {
    FOR(k, n) FOR(i, n) {
        //FOR(j, n) mat[i][j] = mat[i][k] + mat[k][j];
        if(mat[i][k]) mat[i] |= mat[k];
    }
    double res = 0;
    FOR(i, n) {
        res += 1.0 / mat[i].count();
    }
    return res;
}

int main() {
    scanf("%d", &T);
    for(int t = 1; t <= T; ++t) {
        scanf("%d", &n);
        init();
        for(int i = 1, k, v; i <= n; ++i) {
            scanf("%d", &k);
            while(k--) {
                scanf("%d", &v);
                mat[v].set(i);
            }
        }
        printf("Case #%d: %.5f\n", t, solve());
    }
}
