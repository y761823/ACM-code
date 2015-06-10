#include <cstdio>
#include <algorithm>
#include <cstring>
#include <iostream>
#include <cmath>
#include <vector>
#include <map>
using namespace std;
typedef long long LL;
typedef pair<int, int> PII;

const double PI = acos(-1.0);
const double EPS = 1e-8;

inline int sgn(double x) {
    return (x > EPS) - (x < -EPS);
}

struct Point {
    double x, y;
    Point() {}
    Point(double x, double y): x(x), y(y) {}
    void read() {
        scanf("%lf%lf", &x, &y);
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
    double length() const {
        return sqrt(x * x + y * y);
    }
    Point unit() const {
        double l = length();
        return Point(x / l, y / l);
    }
};

double dist(const Point &p1, const Point &p2) {
    return (p1 - p2).length();
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

struct Seg {
    Point st, ed;
    Seg() {}
    Seg(Point st, Point ed): st(st), ed(ed) {}
    void read() {
        st.read(); ed.read();
    }
};
typedef Seg Line;
//return Ax + By + C =0 's A, B, C
void Coefficient(const Line &L, double &A, double &B, double &C) {
    A = L.ed.y - L.st.y;
    B = L.st.x - L.ed.x;
    C = L.ed.x * L.st.y - L.st.x * L.ed.y;
}
//point of intersection
Point operator * (const Line &a, const Line &b) {
    double A1, B1, C1;
    double A2, B2, C2;
    Coefficient(a, A1, B1, C1);
    Coefficient(b, A2, B2, C2);
    Point I;
    I.x = - (B2 * C1 - B1 * C2) / (A1 * B2 - A2 * B1);
    I.y =   (A2 * C1 - A1 * C2) / (A1 * B2 - A2 * B1);
    return I;
}

double Point_to_Line(const Point &p, const Line &L) {
    return fabs(cross(p, L.st, L.ed)/dist(L.st, L.ed));
}

Point reflection(const Point &p, const Line &l) {
    Point t = rotate(l.ed - l.st, -PI / 2);
    return p + t.unit() * (2 * Point_to_Line(p, l));
}

vector<Point> p_vec, p_buf;

struct Poly {
    vector<int> id;
    void add(int i) {
        id.push_back(i);
    }
    Point& operator [] (int i) const {
        return p_vec[id[i]];
    }
};

vector<Poly> pol_vec, pol_buf;
map<PII, int> edge_map;

Point paper[] = {Point(0, 0), Point(0, 1), Point(1, 1), Point(1, 0)};

void reflection(const Poly &pol, const Line &l) {
    for(int i = 0; i < int(pol.id.size()); ++i)
        if(pol.id[i] < int(p_buf.size())) p_buf[pol.id[i]] = reflection(pol[i], l);
}

int intersection(int id1, int id2, const Point &p1, const Point &p2) {
    map<PII, int>::iterator it = edge_map.find(make_pair(id1, id2));
    if(it == edge_map.end()) {
        p_vec.push_back(Line(p_vec[id1], p_vec[id2]) * Line(p1, p2));
        edge_map[make_pair(id1, id2)] = edge_map[make_pair(id1, id2)] = p_vec.size() - 1;
        return p_vec.size() - 1;
    } else return it->second;
}

void fold(const Point &p1, const Point &p2, const Poly &pol) {
    Poly res1, res2;
    int last_s = sgn(cross(p1, pol[0], p2));
    for(int i = 1; i < int(pol.id.size()); ++i) {
        int now_s = sgn(cross(p1, pol[i], p2));
        if(now_s == 0) {
            res1.add(pol.id[i]);
            res2.add(pol.id[i]);
        } else if(now_s < 0) {
            if(last_s > 0) {
                int k = intersection(pol.id[i - 1], pol.id[i], p1, p2);
                res1.add(k);
                res2.add(k);
            }
            res1.add(pol.id[i]);
        } else if(now_s > 0) {
            if(last_s < 0) {
                int k = intersection(pol.id[i - 1], pol.id[i], p1, p2);
                res1.add(k);
                res2.add(k);
            }
            res2.add(pol.id[i]);
        }
        last_s = now_s;
    }
    if(res1.id.size() > 2) {
        res1.add(res1.id[0]);
        reflection(res1, Line(p1, p2));
        reverse(res1.id.begin(), res1.id.end());
        pol_buf.push_back(res1);
    }
    if(res2.id.size() > 2) {
        res2.add(res2.id[0]);
        pol_buf.push_back(res2);
    }
}

void fold(const Point &p1, const Point &p2) {
    p_buf = p_vec;
    edge_map.clear();
    pol_buf.clear();
    for(int i = 0; i < int(pol_vec.size()); ++i)
        fold(p1, p2, pol_vec[i]);
    pol_vec = pol_buf;
    for(int i = 0; i < int(p_buf.size()); ++i)
        p_vec[i] = p_buf[i];
}

void dfs(vector<bool> &vis, int id, const Line &l) {
    vis[id] = true;
    Poly &pol = pol_vec[id];
    for(int i = 0; i < int(pol.id.size() - 1); ++i) {
        if(sgn(cross(l.ed, pol[i], l.st)) == 0 && sgn(cross(l.ed, pol[i + 1], l.st)) == 0) continue;
        int id1 = pol.id[i], id2 = pol.id[i + 1];
        for(int j = 0; j < int(pol_vec.size()); ++j) {
            if(vis[j]) continue;
            for(int k = 0; k < int(pol_vec[j].id.size() - 1); ++k) {
                if(pol_vec[j].id[k] == id1 && pol_vec[j].id[k + 1] == id2) {
                    dfs(vis, j, l);
                    break;
                }
            }
        }
    }
}

int cut(const Line &l) {
    int ret = 0;
    vector<bool> vis(p_vec.size());
    for(int i = 0; i < int(pol_vec.size()); ++i) {
        if(!vis[i]) {
            dfs(vis, i, l);
            ++ret;
        }
    }
    return ret;
}

int main() {
    int T;
    scanf("%d", &T);
    Poly init_pol;
    for(int i = 0; i <= 4; ++i) init_pol.add(i & 3);
    while(T--) {
        int n;
        scanf("%d", &n);
        p_vec.clear();
        pol_vec.clear();
        for(int i = 0; i < 4; ++i) p_vec.push_back(paper[i]);
        for(int i = 0; i <= 4; ++i) pol_vec.push_back(init_pol);
        Point p1, p2;
        for(int i = 0; i <= n; ++i) {
            p1.read(), p2.read();
            fold(p1, p2);
        }
        printf("%d\n", cut(Line(p1, p2)));
    }
}
