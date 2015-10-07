#include <cstdio>
#include <iostream>
#include <algorithm>
#include <cstring>
#include <cmath>
#include <complex>
using namespace std;
typedef long long LL;
#define REP(i, n) for(int i = 0; i < n; ++i)
#define foreach(it, vec) for(__typeof(vec.begin()) it = vec.begin(); it != vec.end(); ++it)

typedef complex<int> Point;
#define x real()
#define y imag()

int dot(const Point &a, const Point &b) {
    return a.x * b.x + a.y * b.y;
}
int cross(const Point &a, const Point &b) {
    return a.x * b.y - a.y * b.x;
}
int dis2(const Point &a, const Point &b) {
    return norm(a - b);
}

Point p[5];
int T, n = 4;

bool check_square() {
    int len = dis2(p[0], p[1]);
    for(int i = 1; i < n; ++i)
        if(dis2(p[i], p[i + 1]) != len) return false;
    if(dot(p[2] - p[1], p[1] - p[0])) return false;
    puts("Square");
    return true;
}

bool check_diamond() {
    int len = dis2(p[0], p[1]);
    for(int i = 1; i < n; ++i)
        if(dis2(p[i], p[i + 1]) != len) return false;
    puts("Diamond");
    return true;
}

bool check_rectangle() {
    if(cross(p[1] - p[0], p[3] - p[2])) return false;
    if(cross(p[0] - p[3], p[1] - p[2])) return false;
    if(dot(p[2] - p[1], p[1] - p[0])) return false;
    puts("Rectangle");
    return true;
}

bool check_parallelogram() {
    if(cross(p[1] - p[0], p[3] - p[2])) return false;
    if(cross(p[0] - p[3], p[1] - p[2])) return false;
    puts("Parallelogram");
    return true;
}

int main() {
    scanf("%d", &T);
    for(int t = 1 ; t <= T; ++t) {
        for(int i = 0, a, b; i < n; ++i) {
            scanf("%d%d", &a, &b);
            p[i] = Point(a, b);
        }
        p[n] = p[0];
        printf("Case #%d: ", t);
        if(!check_square() && !check_diamond() && !check_rectangle() && !check_parallelogram())
            puts("Others");
    }
}
