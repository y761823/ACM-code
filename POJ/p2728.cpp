#include <cstdio>
#include <cmath>
#include <cstring>

const int MAXN = 1010;
const double EPS = 1e-6;

int x[MAXN], y[MAXN], z[MAXN];
bool used[MAXN];
double a[MAXN], b[MAXN], d[MAXN];
int n;
double ans, l, p, q;

inline int abs(int x){
    return x > 0 ? x : -x;
}

inline double horDis(int a, int b){
    double xx = x[a] - x[b], yy = y[a] - y[b];
    return sqrt(xx*xx + yy*yy);
}

void prim(){
    memset(used, 0, sizeof(used));
    used[0] = true;
    for(int i = 1; i < n; ++i){
        a[i] = abs(z[i] - z[0]);
        b[i] = horDis(i,0);
        d[i] = a[i] - l * b[i];
    }
    for(int cnt = 1; cnt < n; ++cnt){
        double mind = 1e10;
        int pos = 0;
        for(int i = 0; i < n; ++i){
            if(!used[i] && d[i] < mind) mind = d[i], pos = i;
        }
        used[pos] = true;
        p += a[pos]; q += b[pos];
        for(int i = 0; i < n; ++i) if(!used[i]){
            double tmpa = abs(z[i] - z[pos]), tmpb = horDis(i, pos);
            if(tmpa - l * tmpb < d[i])
                a[i] = tmpa, b[i] = tmpb, d[i] = tmpa - l * tmpb;
        }
    }
}

int main(){
    while(scanf("%d", &n)!=EOF){
        if(n == 0) break;
        for(int i = 0; i < n; ++i) scanf("%d%d%d", &x[i], &y[i], &z[i]);
        l = 0;
        do{
            ans = l; p = q = 0.0;
            prim();
            l = p / q;
        }while(fabs(ans - l) > EPS);
        printf("%.3f\n", ans);
    }
}
