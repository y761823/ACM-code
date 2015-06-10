#include <cstdio>
#include <cmath>
#include <algorithm>
using namespace std;

const double EPS = 1e-6;

inline int sgn(const double &x) {
    if(fabs(x) < EPS) return 0;
    return x > 0 ? 1 : -1;
}

struct Point {
    double x, y;
    int v, l;
};

inline bool Cross(Point &sp, Point &ep, Point &op) {
    return (sp.x - op.x) * (ep.y - op.y) - (ep.x - op.x) * (sp.y - op.y) >= 0;
}

inline double dist(Point &a, Point &b) {
    return sqrt((a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y));
}

inline bool cmp(const Point &a, const Point &b) {
    if(a.y == b.y) return a.x < b.x;
    return a.y < b.y;
}

const int MAXN = 20;
int stk[MAXN];
bool cut[MAXN], ans[MAXN];
Point p[MAXN], a[MAXN];
int n, top;
double answood;

double Graham_scan(int n) {
    sort(p, p + n, cmp);
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
    double sum = 0;
    stk[++top] = stk[0];
    for(int i = 0; i < top; ++i)
        sum += dist(p[stk[i]], p[stk[i+1]]);
    return sum;
}

int minval, mincut, sumval, sumlen;
double uselen;

void setans(int cutcnt) {
    for(int i = 1; i <= n; ++i) ans[i] = cut[i];
    minval = sumval;
    mincut = cutcnt;
    answood = sumlen - uselen;
}

void dfs(int dep, int cutcnt) {
    if(dep == n + 1) {
        if(n == cutcnt) return ;
        sumval = sumlen = 0;
        for(int i = 1; i <= n; ++i) {
            if(!cut[i]) continue;
            sumval += a[i].v;
            sumlen += a[i].l;
        }
        if(sumval > minval) return ;
        if(sumval == minval && cutcnt >= mincut) return ;
        if(n - cutcnt == 1) {
            uselen = 0;
            setans(cutcnt);
        }
        else if(n - cutcnt == 2) {
            int i1 = 0, i2 = 0;
            for(int i = 1; i <= n; ++i) {
                if(cut[i]) continue;
                if(!i1) i1 = i;
                else i2 = i;
            }
            uselen = 2 * dist(a[i1], a[i2]);
            if(uselen <= sumlen) setans(cutcnt);
        }
        else {
            int pcnt = 0;
            for(int i = 1; i <= n; ++i) {
                if(cut[i]) continue;
                p[pcnt++] = a[i];
            }
            uselen = Graham_scan(pcnt);
            if(sgn(uselen - sumlen) <= 0) setans(cutcnt);
        }
        return ;
    }
    cut[dep] = false;
    dfs(dep + 1, cutcnt);
    cut[dep] = true;
    dfs(dep + 1, cutcnt + 1);
}

int main() {
    int ca = 1;
    while(scanf("%d", &n) != EOF && n) {
        for(int i = 1; i <= n; ++i) {
            scanf("%lf%lf%d%d", &a[i].x, &a[i].y, &a[i].v, &a[i].l);
        }
        mincut = MAXN;
        minval = 0x7fffffff;
        dfs(1, 0);
        if(ca != 1) printf("\n");
        printf("Forest %d\n", ca++);
        printf("Cut these trees:");
        for(int i = 1; i <= n; ++i) if(ans[i]) printf(" %d", i);
        printf("\nExtra wood: %.2f\n", answood);
    }
}
