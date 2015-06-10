#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>
#include <string>
#include <map>
using namespace std;

int inv[7];

struct MOD7 {
    int val;
    MOD7() {}
    MOD7(int val): val((val + 7) % 7) {}
    MOD7 operator + (const MOD7 &rhs) const {
        return MOD7(val + rhs.val);
    }
    MOD7 operator - (const MOD7 &rhs) const {
        return MOD7(val - rhs.val);
    }
    MOD7 operator * (const MOD7 &rhs) const {
        return MOD7(val * rhs.val);
    }
    MOD7 operator / (const MOD7 &rhs) const {
        return MOD7(val * inv[rhs.val]);
    }
    void operator -= (const MOD7 &rhs) {
        val = (val - rhs.val + 7) % 7;
    }
    bool isZero() {
        return val == 0;
    }
    void inc() {
        val = (val + 1) % 7;
    }
    void print() {
        if(val < 3) printf("%d", val + 7);
        else printf("%d", val);
    }
};

map<string, int> mymap;

void init() {
    for(int i = 1; i < 7; ++i) {
        inv[i] = 1;
        for(int j = 1; j < 6; ++j) inv[i] = (inv[i] * i) % 7;
    }
    mymap["MON"] = 1;
    mymap["TUE"] = 2;
    mymap["WED"] = 3;
    mymap["THU"] = 4;
    mymap["FRI"] = 5;
    mymap["SAT"] = 6;
    mymap["SUN"] = 0;
}

const int MAXN = 310;

MOD7 mat[MAXN][MAXN];
int n, m;

int guess_eliminatioin() {
    int rank = 0;
    for(int i = 0, t = 0; i < m && t < n; ++i, ++t) {
        int r = i;
        for(int j = i + 1; j < m; ++j)
            if(mat[r][t].val < mat[j][t].val) r = j;
        if(mat[r][t].isZero()) { --i; continue;}
        else ++rank;
        if(r != i) for(int j = 0; j <= n; ++j) swap(mat[i][j], mat[r][j]);
        for(int j = n; j >= t; --j)
            for(int k = i + 1; k < m; ++k) mat[k][j] -= mat[i][j] * mat[k][t] / mat[i][t];
    }
    for(int i = rank; i < m; ++i)
        if(!mat[i][n].isZero()) return -1;
    if(rank < n) return 0;
    for(int i = n - 1; i >= 0; --i) {
        for(int j = i + 1; j < n; ++j)
            mat[i][n] -= mat[j][n] * mat[i][j];
        mat[i][n] = mat[i][n] / mat[i][i];
    }
    return 1;
}

int main() {
    init();
    while(scanf("%d%d", &n, &m) != EOF) {
        if(n == 0 && m == 0) break;
        memset(mat, 0, sizeof(mat));
        int t, p;
        string s1, s2;
        for(int i = 0; i < m; ++i) {
            cin>>t>>s1>>s2;
            while(t--) {
                scanf("%d", &p);
                mat[i][p - 1].inc();
            }
            mat[i][n] = MOD7(mymap[s2] - mymap[s1] + 8);
        }
        int result = guess_eliminatioin();
        if(result == -1) puts("Inconsistent data.");
        else if(result == 0) puts("Multiple solutions.");
        else {
            for(int i = 0; i < n - 1; ++i) {
                mat[i][n].print();
                putchar(' ');
            }
            mat[n - 1][n].print();
            puts("");
        }
    }
}
