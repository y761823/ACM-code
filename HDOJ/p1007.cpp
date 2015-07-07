////////////////////System Comment////////////////////
////Welcome to Hangzhou Dianzi University Online Judge
////http://acm.hdu.edu.cn
//////////////////////////////////////////////////////
////Username: y761823
////Nickname: Oyk
////Run ID: 
////Submit time: 2014-05-03 12:06:48
////Compiler: GUN C++
//////////////////////////////////////////////////////
////Problem ID: 1007
////Problem Title: 
////Run result: Accept
////Run time:1312MS
////Run memory:3424KB
//////////////////System Comment End//////////////////
#include <cstring>
#include <cstdio>
#include <cmath>
#include <algorithm>
#include <vector>
using namespace std;
typedef long long LL;

struct Point {
    double x, y;
    Point() {}
    Point(double x, double y): x(x), y(y) {}
    void read() {
        scanf("%lf%lf", &y, &x);
    }
    double length() {
        return sqrt(x * x + y * y);
    }
    Point operator - (const Point &rhs) const {
        return Point(x - rhs.x, y - rhs.y);
    }
};

double dist(const Point &a, const Point &b) {
    return (a - b).length();
}

bool x_cmp(const Point &a, const Point &b) {
    return a.x < b.x;
}

bool y_cmp(const Point &a, const Point &b) {
    return a.y < b.y;
}

const int MAXN = 100010;

Point p[MAXN];
double ans;
int n;

double closest_pair(Point *p, int n) {
    if(n <= 1) return 1e100;
    int mid = n / 2;
    double x = p[mid].x;
    double res = min(closest_pair(p, mid), closest_pair(p + mid, n - mid));
    inplace_merge(p, p + mid, p + n, y_cmp);
    vector<Point> q;
    for(int i = 0; i < n; ++i) {
        if(fabs(p[i].x - x) >= res) continue;
        for(vector<Point>::reverse_iterator it = q.rbegin(); it != q.rend(); ++it) {
            if(p[i].y - it->y >= res) break;
            res = min(res, dist(p[i], *it));
        }
        q.push_back(p[i]);
    }
    return res;
}

int main() {
    while(scanf("%d", &n) != EOF && n) {
        for(int i = 0; i < n; ++i) p[i].read();
        sort(p, p + n, x_cmp);
        printf("%.2f\n", closest_pair(p, n) / 2);
    }
}
