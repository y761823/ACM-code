#include <cstdio>
#include <cmath>

const int MAXN = 50;
const double EPS = 1e-6;

struct Point3D {
    double x, y, z;
    Point3D(double xx = 0, double yy = 0, double zz = 0):
        x(xx), y(yy), z(zz) {}
};

Point3D operator - (const Point3D &a, const Point3D &b) {
    return Point3D(a.x - b.x, a.y - b.y, a.z - b.z);
}

double dist(const Point3D &a, const Point3D &b) {
    Point3D c = a - b;
    return sqrt(c.x * c.x + c.y * c.y + c.z * c.z);
}

Point3D p[MAXN];
int n;

void solve() {
    Point3D s;
    double delta = 100, ans = 1e20;
    while(delta > EPS) {
        int d = 0;
        for(int i = 1; i < n; ++i)
            if(dist(s, p[i]) > dist(s,p[d])) d = i;
        double maxd = dist(s, p[d]);
        if(ans > maxd) ans = maxd;
        s.x += (p[d].x - s.x)/maxd*delta;
        s.y += (p[d].y - s.y)/maxd*delta;
        s.z += (p[d].z - s.z)/maxd*delta;
        delta *= 0.98;
    }
    printf("%.5f\n", ans);
}

int main() {
    while(scanf("%d", &n) != EOF && n) {
        for(int i = 0; i < n; ++i) scanf("%lf%lf%lf", &p[i].x, &p[i].y, &p[i].z);
        solve();
    }
}
