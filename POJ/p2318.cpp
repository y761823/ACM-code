#include <cstdio>
#include <cmath>
#include <cstring>

#define EPS 1e-6
#define MAX 5010

typedef long long TYPE;
//2D point
struct Point2 {
    TYPE x, y;
    Point2() {}
    Point2(double xx, double yy): x(xx), y(yy) {};

    bool operator < (const Point2 B) const{
        if(x == B.x) return y < B.y;
        else return x < B.x;
    }
};
//if return>0 then a is on the clockwise of b
TYPE cross(const Point2 &a, const Point2 &b, const Point2 &o){
    return (o.x - a.x) * (o.y - b.y) - (o.x - b.x) * (o.y - a.y);
}

int n, m;
int ans[MAX];
Point2 up[MAX], down[MAX];

void bfind(TYPE x, TYPE y){
    int l = 1, r = n+1;
    Point2 tmp(x, y);
    if(cross(up[1], down[1], tmp) < 0) {++ans[0]; return ;}
    while(l != r-1){
        int mid = (l+r)>>1;
        if(cross(up[mid], down[mid], tmp) > 0) l = mid;
        else r = mid;
    }
    ++ans[l];
}

int main(){
    int x1, y1, x2, y2, x, y, U, L;
    bool flag = false;
    while(scanf("%d%d%d%d%d%d", &n, &m, &x1, &y1, &x2, &y2) != EOF){
        if(n == 0) break;
        if(flag) printf("\n");
        flag = true;
        up[0].x = down[0].x = x1;
        up[0].y = y1; down[0].y = y2;
        for(int i = 1; i <= n; ++i){
            scanf("%d%d", &U, &L);
            up[i].x = U; down[i].x = L;
            up[i].y = y1; down[i].y = y2;
        }
        memset(ans, 0, sizeof(ans));
        for(int i = 0; i < m; ++i){
            scanf("%d%d", &x, &y);
            bfind(x, y);
        }
        for(int i = 0; i <= n; ++i)
            printf("%d: %d\n", i, ans[i]);
    }
    return 0;
}
