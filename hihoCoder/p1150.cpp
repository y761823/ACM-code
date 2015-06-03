#include <cstdio>
#include <cstring>
#include <algorithm>
#include <iostream>
#include <cmath>
#include <cassert>
using namespace std;
typedef long long LL;

const int MAXN = 1010;

int ax[MAXN], ay[MAXN], bx[MAXN], by[MAXN];
int a, b, n, m, T;
int now_x, now_y;

LL sqr(int x, int y) {
    return LL(x) * x + LL(y) * y;
}

LL calc(int x, int y) {
    LL res = 0x3f3f3f3f;
    for(int i = 0; i < b; ++i)
        res = min(res, LL(abs(x - bx[i]) + abs(y - by[i])));
    for(int i = 0; i < a; ++i)
        res += sqr(x - ax[i], y - ay[i]);
    return res;
}

LL get_ans(int x, int y) {
    LL res = ~(1LL << 63);
    for(int i = -1; i <= 1; ++i)
        for(int j = -1; j <= 1; ++j) res = min(res, calc(x + i, y + j));
    return res;
}

LL solve() {
    static int fx[] = {1, 0, -1, 0};
    static int fy[] = {0, 1, 0, -1};

    int x = (n + 1) / 2, y = (n + 1) / 2;
    double step = max(n, m) / 2, v = 0.95;
    LL res = calc(x, y);

    while(step > 1e-4) {
        int p = int(ceil(step));
        for(int f = 0; f < 4; ++f) {
            int new_x = x + p * fx[f], new_y = y + p * fy[f];
            LL tmp = calc(new_x, new_y);
            if(tmp < res) {
                res = tmp;
                x = new_x, y = new_y;
            }
        }
        step *= v;
    }
    //cout<<res<<" # debug #"<<endl; assert(get_ans(x, y) == res);
    return get_ans(x, y);
}

LL test() {
    LL res = ~(1LL << 63);
    for(int i = 1; i <= n; ++i)
        for(int j = 1; j <= m; ++j) res = min(res, calc(i, j));
    return res;
}

int main() {
    //freopen("input.txt", "r", stdin);
    scanf("%d", &T);
    for(int t = 1; t <= T; ++t) {
        scanf("%d%d%d%d", &n, &m, &a, &b);
        for(int i = 0; i < a; ++i) scanf("%d%d", &ax[i], &ay[i]);
        for(int i = 0; i < b; ++i) scanf("%d%d", &bx[i], &by[i]);
        //cout<<calc(2, 2)<<endl;
        cout<<"Case #"<<t<<": "<<solve()<<endl;
        //cout<<"#debug "<<test()<<endl;
    }
}
