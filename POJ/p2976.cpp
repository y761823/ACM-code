#include <cstdio>
#include <algorithm>
#include <cmath>
#include <functional>
#define MAXN 1010
#define EPS 1e-6
#define LL long long
using namespace std;

int n,k;
int a[MAXN], b[MAXN];
double ans;

struct node{
    int c;
    double d;
    bool operator < (const node &a) const{
        return d > a.d;
    }
} d[MAXN];

void doit(){
    double l = 1;
    int m = n - k;
    do{
        ans = l;
        for(int i = 0; i < n; ++i) {d[i].d = a[i] - l * b[i]; d[i].c = i;};
        sort(d, d+n);
        LL p = 0, q = 0;
        for(int i = 0; i < m; ++i) {p += a[d[i].c]; q += b[d[i].c];};
        l = double(p) / q;
    } while(fabs(ans - l) > EPS);
}

int main(){
    while(scanf("%d%d",&n,&k)!=EOF){
        if(n == 0 && k == 0) break;
        for(int i = 0; i < n; ++i) scanf("%d",&a[i]);
        for(int i = 0; i < n; ++i) scanf("%d",&b[i]);
        doit();
        printf("%d\n",(int)floor(100*ans + 0.5));
    }
}
