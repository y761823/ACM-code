#include <cstdio>
#include <cmath>
#include <cstring>
#include <algorithm>

struct POINT {
	int x, y;
	POINT(int xx = 0, int yy = 0): x(xx), y(yy) {}
};

const int MAXN = 1010;
const double PI = acos(-1.0);

int n, L;
int stk[MAXN], top;
POINT p[MAXN];

inline bool cmp(const POINT &a, const POINT &b) {
	if(a.y == b.y) return a.x < b.x;
	return a.y < b.y;
}
//turn left
inline bool Cross(POINT &sp, POINT &ep, POINT &op) {
	return (sp.x - op.x) * (ep.y - op.y) - (ep.x - op.x) * (sp.y - op.y) >= 0;
}

inline double dist(POINT &a, POINT &b) {
	return sqrt((a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y));
}

void Graham_scan() {
	std::sort(p, p + n, cmp);
	top = 1;
	stk[0] = 0; stk[1] = 1;
	for(int i = 2; i < n; ++i) {
		while(top && Cross(p[i], p[stk[top]], p[stk[top - 1]])) --top;
		stk[++top] = i;
	}
	int len = top;
	stk[++top] = n - 2;
	for(int i = n - 3; i >= 0; --i) {
		while(top != len && Cross(p[i], p[stk[top]], p[stk[top - 1]])) --top;
		stk[++top] = i;
	}
}

void solve() {
	double ans = L * PI * 2;
	stk[++top] = stk[0];
	for(int i = 0; i < top; ++i)
		ans += dist(p[stk[i]], p[stk[i+1]]);
	printf("%d\n", int(ans+0.5));
}

int main() {
	while(scanf("%d%d", &n, &L) != EOF) {
		for(int i = 0; i < n; ++i) scanf("%d%d", &p[i].x, &p[i].y);
		Graham_scan();
		solve();
	}
}
