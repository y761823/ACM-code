#include <cstdio>
#include <algorithm>
#include <iostream>
#include <cstring>
#include <vector>
#include <complex>
using namespace std;
typedef long long LL;

const double EPS = 1e-10;
int sgn(double x) {
    return (x > EPS) - (x < -EPS);
}

typedef complex<double> Point;
#define x real()
#define y imag()

int type(const Point &p) {
    if(p.y != 0) return p.y < 0;
    return p.x < 0;
}
double cross(const Point &a, const Point &b) { // res > 0 means a on right
    return a.x * b.y - a.y * b.x;
}
double cross(const Point &o, const Point &a, const Point &b) { // res < 0 means turn right
    return cross(a - o, b - o);
}
Point intersection(const Point &u1, const Point &u2, const Point &v1, const Point &v2) {
    double t = cross(u1 - v1, v1 - v2) / cross(u1 - u2, v1 - v2);
    return u1 + (u2 - u1) * t;
}
bool cmp_ang(const Point &a, const Point &b) {
    if(type(a) != type(b)) return type(a) < type(b);
    return cross(a, b) > 0;
}

struct Line {
    Point s, e; double angle;
    Line(Point s = 0, Point e = 0): s(s), e(e) {}
    double get_angle() {
        return angle = arg(e - s);
    }
    Point operator * (const Line &rhs) const {
        return intersection(s, e, rhs.s, rhs.e);
    }
    bool operator < (const Line &rhs) const {
        return angle < rhs.angle;
    }
};

typedef vector<Point> Polygon;
double get_area(const Polygon& p) {
    double res = cross(p.back(), p.front());
    for(size_t i = 0; i < p.size() - 1; ++i)
        res += cross(p[i], p[i + 1]);
    return fabs(res) / 2;
}

void half_planes_cross(vector<Line> &l, int n, Polygon &poly) {
    for(int i = 0; i < n; ++i) l[i].get_angle();
    sort(l.begin(), l.end());
    vector<Point> q(n);
    int head = 0, tail = 0;
    for(int i = 1; i < n; ++i) {
        while(head != tail && sgn(cross(l[i].s, l[i].e, q[tail - 1])) <= 0) --tail;
        while(head != tail && sgn(cross(l[i].s, l[i].e, q[head])) <= 0) ++head;
        l[++tail] = l[i];
        if(head < tail) q[tail - 1] = l[tail - 1] * l[tail];
    }
    while(head != tail && sgn(cross(l[head].s, l[head].e, q[tail - 1])) <= 0) --tail;
    if(head < tail) q[tail] = l[head] * l[tail];
    poly.assign(q.begin() + head, q.begin() + tail + 1);
}

const int MAXN = 1010;

Point p[MAXN], v[MAXN + MAXN];
vector<Line> l;
int T, n;

double solve() {
    l.clear();
    int k = n / 3;
    for(int c = 0; c < n; ++c) {
        int size = 0;
        for(int i = 0; i < n; ++i) if(i != c)
            v[size++] = p[i] - p[c];
        sort(v, v + size, cmp_ang);
        copy(v, v + size, v + size);
        for(int i = 0, j = 0; i < size; ++i) {
            if(i == j) ++j;
            while(j < i + size && cross(v[i], v[j]) >= 0) ++j;
            if(j - i == k) l.push_back(Line(p[c] + v[i], p[c]));
        }
    }
    Polygon poly;
    half_planes_cross(l, l.size(), poly);
    return get_area(poly);
}

int main() {
    scanf("%d", &T);
    for(int t = 1; t <= T; ++t) {
        scanf("%d", &n);
        for(int i = 0, a, b; i < n; ++i) {
            scanf("%d%d", &a, &b);
            p[i] = Point(a, b);
        }
        printf("Case #%d: %.6f\n", t, solve());
    }
}
