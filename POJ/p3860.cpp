#include <cstdio>
#include <cstring>
#include <map>
#include <string>
#include <iostream>
#include <algorithm>
using namespace std;
typedef long long LL;

const int MAXN = 220;
const double EPS = 1e-8;

map<string, int> mp;
string a, b;
int m, n;

double x, y;
int aid, bid;
double mat[MAXN][MAXN];

inline int sgn(double x) {
    return (x > EPS) - (x < -EPS);
}

bool floyd() {
    for(int k = 1; k <= n; ++k)
        for(int i = 1; i <= n; ++i) if(mat[i][k] > 0)
            for(int j = 1; j <= n; ++j) if(mat[k][j] > 0)
                if(mat[i][k] * mat[k][j] > mat[i][j]) mat[i][j] = mat[i][k] * mat[k][j];
                /*
    for(int k = 1; k <= n; ++k)
        for(int i = 1; i <= n; ++i) if(mat[i][k] > 0)
            for(int j = 1; j <= n; ++j) if(mat[k][j] > 0)
                if(mat[i][j] > 0 && sgn(mat[i][k] * mat[k][j] - mat[i][j]) == 1) return false;*/
    for(int i = 1; i <= n; ++i)
        for(int j = i + 1; j <= n; ++j) {
            if(mat[i][j] < 0 || mat[j][i] < 0) continue;
            if(sgn(mat[i][j] * mat[j][i] - 1) > 0) return false;
        }
    return true;
}

int main() {
    ios::sync_with_stdio(false);
    while(cin>>m) {
        if(m == 0) break;
        n = 0;
        mp.clear();
        for(int i = 1; i < MAXN; ++i) {
            for(int j = 1; j < MAXN; ++j) mat[i][j] = -1;
            mat[i][i] = 1;
        }
        for(int i = 0; i < m; ++i) {
            cin>>x>>a>>y>>b;
            if(mp.find(a) != mp.end()) aid = mp[a];
            else mp[a] = aid = ++n;
            if(mp.find(b) != mp.end()) bid = mp[b];
            else mp[b] = bid = ++n;
            //if(mat[aid][bid] < double(x, y)) mat[aid][bid] = double(x, y);
            if(mat[bid][aid] < x / y) mat[bid][aid] = x / y;
        }
        cin>>x>>a>>y>>b;
        if(!floyd()) {
            puts("INCONSISTENT");
            continue;
        }
        if(mp.find(a) == mp.end() || mp.find(b) == mp.end()) {
            puts("UNAVAILABLE");
            continue;
        }
        aid = mp[a];
        bid = mp[b];
        if(sgn(mat[aid][bid] - y / x) == 0  && sgn(mat[bid][aid] - x / y) == 0) {
            puts("==");
            continue;
        }
        if(mat[bid][aid] > 0 && sgn(mat[bid][aid] - x / y) >= 0) {
            puts("<=");
            continue;
        }
        if(mat[aid][bid] > 0 && sgn(mat[aid][bid] - y / x) >= 0) {
            puts(">=");
            continue;
        }
        puts("UNAVAILABLE");
    }
}
