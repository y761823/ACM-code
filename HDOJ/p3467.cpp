////////////////////System Comment////////////////////
////Welcome to Hangzhou Dianzi University Online Judge
////http://acm.hdu.edu.cn
//////////////////////////////////////////////////////
////Username: y761823
////Nickname: Oyk
////Run ID: 
////Submit time: 2013-11-14 23:47:20
////Compiler: GUN C++
//////////////////////////////////////////////////////
////Problem ID: 3467
////Problem Title: 
////Run result: Accept
////Run time:15MS
////Run memory:328KB
//////////////////System Comment End//////////////////
#include <cstdio>
#include <iostream>
#include <cstring>
#include <algorithm>
#include <vector>
#include <cmath>
using namespace std;

const double PI = acos(-1.0);
const double EPS = 1e-8;

double Deg2Rad(double deg){return (deg * PI / 180.0);}
double Rad2Deg(double rad){return (rad * 180.0 / PI);}
double Sin(double deg){return sin(Deg2Rad(deg));}
double Cos(double deg){return cos(Deg2Rad(deg));}
double ArcSin(double val){return Rad2Deg(asin(val));}
double ArcCos(double val){return Rad2Deg(acos(val));}
double Sqrt(double val){return sqrt(val);}

inline int sgn(double x) {
    return (x > EPS) - (x < -EPS);
}

inline double sqr(double x) {
    return x * x;
}

struct Point {
    double x, y;
    Point() {}
    Point(double x, double y): x(x), y(y) {}
    void read() {
        scanf("%lf%lf", &x, &y);
    }
    double length() const {
        return sqrt(x * x + y * y);
    }
    Point operator + (const Point &rhs) const {
        return Point(x + rhs.x, y + rhs.y);
    }
    Point operator - (const Point &rhs) const {
        return Point(x - rhs.x, y - rhs.y);
    }
    Point operator * (double t) const {
        return Point(x * t, y * t);
    }
    Point operator / (double t) const {
        return Point(x / t, y / t);
    }
    Point unit() const {
        double l = length();
        return *this / l;
    }
    double angle() const {
        return atan2(y, x);
    }
};

double dist(const Point &a, const Point &b) {
    return (a - b).length();
}

Point rotate(const Point &p, double angle, const Point &o = Point(0, 0)) {
    Point t = p - o;
    double x = t.x * cos(angle) - t.y * sin(angle);
    double y = t.y * cos(angle) + t.x * sin(angle);
    return Point(x, y) + o;
}

double cross(const Point &a, const Point &b) {
    return a.x * b.y - a.y * b.x;
}

double cross(const Point &sp, const Point &ep, const Point &op) {
    return cross(sp - op, ep - op);
}

struct Region {
    double st, ed;
    Region() {}
    Region(double st, double ed): st(st), ed(ed) {}
};

struct Circle {
    Point c;
    double r;
    Circle() {}
    Circle(Point c, double r): c(c), r(r) {}
    void read() {
        c.read();
        scanf("%lf", &r);
    }
    double area() const {
        return PI * r * r;
    }
    bool contain(const Circle &rhs) const {
        return sgn(dist(c, rhs.c) + rhs.r - r) <= 0;
    }
    bool contain(const Point &p) const {
        return sgn(dist(c, p) - r) <= 0;
    }
    bool intersect(const Circle &rhs) const {
        return sgn(dist(c, rhs.c) - r - rhs.r) < 0;
    }
    bool tangency(const Circle &rhs) const {
        return sgn(dist(c, rhs.c) - r - rhs.r) == 0;
    }
    Point pos(double angle) const {
        Point p = Point(c.x + r, c.y);
        return rotate(p, angle, c);
    }
};

void intersection(const Circle &cir1, const Circle &cir2, Point &p1, Point &p2) {
    double l = dist(cir1.c, cir2.c);
    double d = (sqr(l) - sqr(cir2.r) + sqr(cir1.r)) / (2 * l);
    double d2 = sqrt(sqr(cir1.r) - sqr(d));
    Point mid = cir1.c + (cir2.c - cir1.c).unit() * d;
    Point v = rotate(cir2.c - cir1.c, PI / 2).unit() * d2;
    p1 = mid + v, p2 = mid - v;
}

const int MAXN = 10;


struct Region_vector {
    int n;
    Region v[5];
    void clear() {
        n = 0;
    }
    void add(const Region &r) {
        v[n++] = r;
    }
} *last, *cur;

Circle cir[MAXN];
bool del[MAXN];
double r;
int n = 5;

double CommonArea(const Circle &A, const Circle &B) {
    double area = 0.0;
    const Circle & M = (A.r > B.r) ? A : B;
    const Circle & N = (A.r > B.r) ? B : A;
    double D = dist(M.c, N.c);
    if((D < M.r + N.r) && (D > M.r - N.r)) {
        double cosM = (M.r * M.r + D * D - N.r * N.r) / (2.0 * M.r * D);
        double cosN = (N.r * N.r + D * D - M.r * M.r) / (2.0 * N.r * D);
        double alpha = 2.0 * ArcCos(cosM);
        double beta = 2.0 * ArcCos(cosN);
        double TM = 0.5 * M.r * M.r * Sin(alpha);
        double TN = 0.5 * N.r * N.r * Sin(beta);
        double FM = (alpha / 360.0) * M.area();
        double FN = (beta / 360.0) * N.area();
        area = FM + FN - TM - TN;
    }
    else if(D <= M.r - N.r) {
        area = N.area();
    }
    return area;
}

bool isOnlyOnePoint() {
    bool flag = false;
    Point t;
    for(int i = 0; i < n; ++i)
        for(int j = i + 1; j < n; ++j) {
            if(cir[i].tangency(cir[j])) {
                flag = true;
                t = (cir[i].c + cir[j].c) / 2;
                break;
            }
        }
    if(!flag) return false;
    for(int i = 0; i < n; ++i)
        if(!cir[i].contain(t)) return false;
    printf("Only the point (%.2f, %.2f) is for victory.\n", t.x + EPS, t.y + EPS);
    return true;
}

bool solve() {
    if(isOnlyOnePoint()) return true;
    memset(del, 0, sizeof(del));
    for(int i = 0; i < n; ++i)
        for(int j = 0; j < n; ++j) {
            if(del[j] || i == j) continue;
            if(cir[i].contain(cir[j])) {
                del[i] = true;
                break;
            }
        }
    double ans = 0;
    for(int i = 0; i < n; ++i) {
        if(del[i]) continue;
        last->clear();
        Point p1, p2;
        for(int j = 0; j < n; ++j) {
            if(del[j] || i == j) continue;
            if(!cir[i].intersect(cir[j])) return false;
            cur->clear();
            intersection(cir[i], cir[j], p1, p2);
            double rs = (p2 - cir[i].c).angle(), rt = (p1 - cir[i].c).angle();
            if(sgn(rs) < 0) rs += 2 * PI;
            if(sgn(rt) < 0) rt += 2 * PI;
            if(last->n == 0) {
                if(sgn(rt - rs) < 0) cur->add(Region(rs, 2 * PI)), cur->add(Region(0, rt));
                else cur->add(Region(rs, rt));
            } else {
                for(int k = 0; k < last->n; ++k) {
                    if(sgn(rt - rs) < 0) {
                        if(sgn(last->v[k].st - rt) >= 0 && sgn(rs - last->v[k].ed) >= 0) continue;
                        if(sgn(last->v[k].st - rt) < 0) cur->add(Region(last->v[k].st, min(last->v[k].ed, rt)));
                        if(sgn(rs - last->v[k].ed) < 0) cur->add(Region(max(last->v[k].st, rs), last->v[k].ed));
                    } else {
                        if(sgn(rt - last->v[k].st) <= 0 || sgn(last->v[k].ed - rs) <= 0) continue;
                        cur->add(Region(max(rs, last->v[k].st), min(rt, last->v[k].ed)));
                    }
                }
            }
            swap(last, cur);
            if(last->n == 0) break;
        }
        for(int j = 0; j < last->n; ++j) {
            p1 = cir[i].pos(last->v[j].st);
            p2 = cir[i].pos(last->v[j].ed);
            ans += cross(p1, p2) / 2;
            double angle = last->v[j].ed - last->v[j].st;
            ans += 0.5 * sqr(cir[i].r) * (angle - sin(angle));
        }
    }
    if(sgn(ans) == 0) return false;
    printf("The total possible area is %.2f.\n", ans + EPS);
    //printf("%.2f\n", CommonArea(cir[0], cir[4]));
    return true;
}

int main() {
    last = new Region_vector, cur = new Region_vector;
    while(scanf("%lf", &r) != EOF) {
        Point t;
        for(int i = 0; i < n; ++i) {
            t.read();
            cir[i] = Circle(t, r);
        }
        if(!solve()) puts("Poor iSea, maybe 2012 is coming!");
    }
}
