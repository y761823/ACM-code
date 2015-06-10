#include <cstdio>
#include <algorithm>
#include <cstring>
#include <algorithm>
#include <cmath>
using namespace std;

const int MAXN = 1010;
const double EPS = 1e-10;

int sgn(double x) {
    return (x > EPS) - (x < -EPS);
}

struct Point {
    double x, y;
};
Point p[MAXN];
pair<double, double> l[MAXN];
int n, d;

int solve() {
    for(int i = 0; i < n; ++i) {
        if(p[i].y > d) return -1;
        double t = sqrt(d * d - p[i].y * p[i].y);
        l[i] = make_pair(p[i].x - t, p[i].x + t);
    }

    sort(l, l + n);
    int res = 0;
    double pre = 0;

    for(int i = n - 1; i >= 0; --i) {
        if(res > 0 && sgn(l[i].second - pre) >= 0) continue;
        res++, pre = l[i].first;
    }
    return res;
}

int main() {
    int kase = 0;
    while(scanf("%d%d", &n, &d) != EOF) {
        if(n == 0 && d == 0) break;
        for(int i = 0; i < n; ++i)
            scanf("%lf%lf", &p[i].x, &p[i].y);
        printf("Case %d: %d\n", ++kase, solve());
    }
}
