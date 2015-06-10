#include <cstdio>
#include <cmath>
#include <algorithm>
using namespace std;

const int MAXN = 200010;

struct Point {
	double x, y;
	bool flag;
};

inline double dist(const Point &a, const Point &b) {
    return sqrt((a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y));
}

Point pt[MAXN];

inline bool cmp(const Point &a, const Point &b) {
    if(a.x == b.x) return a.y < b.y;
	return a.x < b.x;
}

double shortest_distance(int pn) {
	double mind = dist(pt[0], pt[pn/2]);
    sort(pt, pt + pn, cmp);
	for(int i = 0; i < pn; ++i) {
        for(int j = i + 1; j < pn; ++j) {
            if(pt[i].flag == pt[j].flag) continue;
            double t = dist(pt[i], pt[j]);
            if(mind > t) mind = t;
            if(pt[j].x - pt[i].x >= mind) break;
        }
	}
	return mind;
}

int main() {
	int T;
	scanf("%d", &T);
	while(T--) {
		int n;
		scanf("%d", &n);
		for(int i = 0; i < n; ++i) {
			scanf("%lf%lf", &pt[i].x, &pt[i].y);
			pt[i].flag = false;
		}
		for(int i = n; i < 2*n; ++i) {
			scanf("%lf%lf", &pt[i].x, &pt[i].y);
			pt[i].flag = true;
		}
		printf("%.3f\n", shortest_distance(2 * n));
	}
}