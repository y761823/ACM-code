//POJ 3621
#include <iostream>
#include <cstdio>
using namespace std;

const int MAXN = 1010, MAXM = 5010;
const double EPS = 1e-6;

int n, m;
int a[MAXN];
int u[MAXM], v[MAXM], b[MAXM];
double d[MAXM];
double dis[MAXN];

bool BellmanFord(double l){
    for(int i = 0; i < m; ++i) d[i] = -(a[v[i]] - l*b[i]);
    for(int i = 1; i <= n; ++i) dis[i] = 0;
    for(int i = 0; i < n; ++i){
        bool flag = false;
        for(int j = 0; j < m; ++j)
            if(dis[v[j]] > dis[u[j]] + d[j]){
                dis[v[j]] = dis[u[j]] + d[j];
                flag = true;
            }
        if(!flag) return false;
    }
    return true;
}

int main(){
    scanf("%d%d", &n, &m);
    for(int i = 1; i <= n; ++i) scanf("%d", &a[i]);
    for(int i = 0; i < m; ++i) scanf("%d%d%d", &u[i], &v[i], &b[i]);
    double l, r, mid;
    l = 0, r = 1000;
    do{
        mid = (r + l)/2;
        if(BellmanFord(mid)) l = mid;
        else r = mid;
    }while(r - l > EPS);
    cout.precision(2);
    if(r > EPS) cout<<fixed<<r<<endl;
    else cout<<0<<endl;
}
