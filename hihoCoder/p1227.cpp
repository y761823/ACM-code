#include <cstdio>
#include <iostream>
#include <algorithm>
#include <cmath>
using namespace std;

const int MAXN = 110;
const double EPS = 1e-10;
const int INF = 0x3f3f3f3f;

inline int sgn(double x) {
    return (x > EPS) - (x < -EPS);
}

double x[MAXN], y[MAXN], dis[MAXN];
int T, m, n;

int solve() {
    if(n > m) return -1;
    int res = -1;
    for(int i = 0; i < m; ++i) {
        for(int j = 0; j < m; ++j) dis[j] = hypot(x[i] - x[j], y[i] - y[j]);
        sort(dis, dis + m);
        int tmp = ceil(dis[n - 1]);
        if(sgn(tmp - dis[n - 1]) == 0) tmp++;
        if(n < m && sgn(tmp - dis[n]) >= 0) continue;
        if(res == -1 || tmp < res) res = tmp;
    }
    return res;
}

int main(){
	scanf("%d", &T);
	while(T--) {
		scanf("%d%d", &m, &n);
		for(int i = 0; i < m; ++i) scanf("%lf%lf", &x[i], &y[i]);
		printf("%d\n", solve());
	}
}
