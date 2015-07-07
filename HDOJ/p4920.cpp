////////////////////System Comment////////////////////
////Welcome to Hangzhou Dianzi University Online Judge
////http://acm.hdu.edu.cn
//////////////////////////////////////////////////////
////Username: y761823
////Nickname: Oyk
////Run ID: 
////Submit time: 2014-09-02 18:44:54
////Compiler: GUN C++
//////////////////////////////////////////////////////
////Problem ID: 4920
////Problem Title: 
////Run result: Accept
////Run time:1625MS
////Run memory:8256KB
//////////////////System Comment End//////////////////
#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>
#include <bitset>
using namespace std;
typedef long long LL;

const int MAXN = 810;

int n;

#define FOR(i, n) for(int i = 0; i < n; ++i)
struct Mat {
    int mat[MAXN][MAXN];
    void read() {
        FOR(i, n) FOR(j, n) scanf("%d", &mat[i][j]), mat[i][j] %= 3;
    }
    void print() {
        FOR(i, n) {
            FOR(j, n - 1) printf("%d ", mat[i][j]);
            printf("%d\n", mat[i][n - 1]);
        }
    }
    void clear() {
        FOR(i, n) FOR(j, n) mat[i][j] = 0;
    }
} A, B, res;

bitset<MAXN> a1[MAXN], a2[MAXN], b1[MAXN], b2[MAXN];

void solve() {
    FOR(i, n) {
        a1[i].reset();
        a2[i].reset();
        b1[i].reset();
        b2[i].reset();
    }
    FOR(i, n) FOR(j, n) {
        if(A.mat[i][j] == 1) a1[i][j] = 1;
        if(A.mat[i][j] == 2) a2[i][j] = 1;
    }
    FOR(j, n) FOR(i, n) {
        if(B.mat[i][j] == 1) b1[j][i] = 1;
        if(B.mat[i][j] == 2) b2[j][i] = 1;
    }
    res.clear();
    FOR(i, n) FOR(j, n) {
        res.mat[i][j] += (a1[i] & b1[j]).count();
        res.mat[i][j] += 2 * (a1[i] & b2[j]).count();
        res.mat[i][j] += 2 * (a2[i] & b1[j]).count();
        res.mat[i][j] += 4 * (a2[i] & b2[j]).count();
        res.mat[i][j] %= 3;
    }
}

int main() {
    while(scanf("%d", &n) != EOF) {
        A.read(); B.read();
        solve();
        res.print();
    }
}
