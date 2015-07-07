////////////////////System Comment////////////////////
////Welcome to Hangzhou Dianzi University Online Judge
////http://acm.hdu.edu.cn
//////////////////////////////////////////////////////
////Username: y761823
////Nickname: Oyk
////Run ID: 
////Submit time: 2013-08-21 23:39:54
////Compiler: GUN C++
//////////////////////////////////////////////////////
////Problem ID: 4565
////Problem Title: 
////Run result: Accept
////Run time:62MS
////Run memory:332KB
//////////////////System Comment End//////////////////
#include <cstdio>
#include <queue>
#include <utility>
#include <iostream>
#include <cstring>
using namespace std;
typedef long long LL;

const int N = 2;

int a, b, n, m;

#define MOD(x) ((x)%m)

struct Mat {
    LL v[N][N];
    Mat operator * (const Mat &rhs) {
        Mat ret;
        for(int i = 0; i < N; ++i)
            for(int j = 0; j < N; ++j) {
                ret.v[i][j] = 0;
                for(int k = 0; k < N; ++k) ret.v[i][j] += MOD(v[i][k] * rhs.v[k][j]);
                ret.v[i][j] %= m;
            }
        return ret;
    }
};

Mat mul(Mat x, int p) {
    Mat ans;
    ans.v[0][0] = ans.v[1][1] = 1;
    ans.v[0][1] = ans.v[1][0] = 0;
    while(p > 0) {
        if(p & 1) ans = ans * x;
        x = x * x;
        p >>= 1;
    }
    return ans;
}

int main() {
    while(scanf("%d%d%d%d", &a, &b, &n, &m) != EOF) {
        Mat tmp;
        tmp.v[0][0] = 2 * a;
        tmp.v[0][1] = - (a * a - b);
        while(tmp.v[0][1] < 0) tmp.v[0][1] += m;
        tmp.v[1][0] = 1;
        tmp.v[1][1] = 0;
        tmp = mul(tmp, n);
        LL ans = MOD(2 * a * tmp.v[1][0] + 2 * tmp.v[1][1]);
        cout<<ans<<endl;
    }
}
