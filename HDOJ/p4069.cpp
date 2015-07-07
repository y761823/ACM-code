////////////////////System Comment////////////////////
////Welcome to Hangzhou Dianzi University Online Judge
////http://acm.hdu.edu.cn
//////////////////////////////////////////////////////
////Username: y761823
////Nickname: Oyk
////Run ID: 
////Submit time: 2014-08-31 00:00:17
////Compiler: GUN C++
//////////////////////////////////////////////////////
////Problem ID: 4069
////Problem Title: 
////Run result: Accept
////Run time:1203MS
////Run memory:392KB
//////////////////System Comment End//////////////////
#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>
#include <vector>
using namespace std;
typedef long long LL;

const int MAXN = 10;
const int MAXC = 9 * 9 * 4 + 10;
const int MAXR = 9 * 9 * 9 + 10;
const int MAXP = MAXR * 4 + MAXC;

struct DLX {
    int sz;
    int sum[MAXC];
    int row[MAXP], col[MAXP];
    int left[MAXP], right[MAXP], up[MAXP], down[MAXP];
    int ansd, ans[MAXR], anscnt;

    void init(int n) {
        for(int i = 0; i <= n; ++i) {
            up[i] = down[i] = i;
            left[i] = i - 1; right[i] = i + 1;
        }
        left[0] = n; right[n] = 0;
        sz = n + 1;
        memset(sum, 0, sizeof(sum));
    }

    void add_row(int r, vector<int> &func) {
        int first = sz;
        for(size_t i = 0; i < func.size(); ++i) {
            int c = func[i];
            left[sz] = sz - 1; right[sz] = sz + 1; up[sz] = up[c]; down[sz] = c;
            down[up[c]] = sz; up[c] = sz;
            row[sz] = r; col[sz] = c;
            ++sum[c], ++sz;
        }
        left[first] = sz - 1; right[sz - 1] = first;
    }

    void remove(int c) {
        left[right[c]] = left[c];
        right[left[c]] = right[c];
        for(int i = down[c]; i != c; i = down[i]) {
            for(int j = right[i]; j != i; j = right[j])
                up[down[j]] = up[j], down[up[j]] = down[j], --sum[col[j]];
        }
    }

    void restore(int c) {
        for(int i = up[c]; i != c; i = up[i]) {
            for(int j = left[i]; j != i; j = left[j])
                up[down[j]] = j, down[up[j]] = j, ++sum[col[j]];
        }
        left[right[c]] = c;
        right[left[c]] = c;
    }

    bool dfs(int d) {
        if(!right[0]) {
            ansd = d;
            return ++anscnt == 2;
        }
        int c = right[0];
        for(int i = right[0]; i != 0; i = right[i]) if(sum[i] < sum[c]) c = i;
        remove(c);
        for(int i = down[c]; i != c; i = down[i]) {
            if(!anscnt) ans[d] = row[i];
            for(int j = right[i]; j != i; j = right[j]) remove(col[j]);
            if(dfs(d + 1)) return true;
            for(int j = left[i]; j != i; j = left[j]) restore(col[j]);
        }
        restore(c);
        return false;
    }

    int solve(vector<int> &v) {
        v.clear();
        anscnt = 0;
        dfs(0);
        if(anscnt == 1) for(int i = 0; i < ansd; ++i) v.push_back(ans[i]);
        return anscnt;
    }
} solver;

const int SLOT = 0;
const int ROW = 1;
const int COL = 2;
const int SUB = 3;

int fr[] = {-1, 0, 1, 0};
int fc[] = {0, 1, 0, -1};
int fp[] = {16, 32, 64, 128};

int mat[MAXN][MAXN];
int val[MAXN][MAXN], cnt;
int T, n = 9;

bool in_n(int x) {
    return 0 <= x && x < n;
}

void dfs(int r, int c, int p) {
    val[r][c] = p;
    for(int i = 0; i < 4; ++i) {
        int nr = r + fr[i], nc = c + fc[i];
        if(in_n(nr) && in_n(nc) && ((fp[i] & mat[r][c]) == 0) && !val[nr][nc])
            dfs(nr, nc, p);
    }
}

void print(int mat[MAXN][MAXN]) {
    for(int i = 0; i < n; ++i) {
        for(int j = 0; j < n; ++j) printf("%d", mat[i][j]);
        puts("");
    }
}

int encode(int a, int b, int c) {
    return a * 81 + b * 9 + c + 1;
}

void decode(int code, int &a, int &b, int &c) {
    --code;
    c = code % 9; code /= 9;
    b = code % 9; code /= 9;
    a = code;
}

int main() {
    scanf("%d", &T);
    for(int kase = 1; kase <= T; ++kase) {
        for(int i = 0; i < n; ++i)
            for(int j = 0; j < n; ++j) scanf("%d", &mat[i][j]);
        memset(val, 0, sizeof(val));
        cnt = 0;
        for(int i = 0; i < n; ++i)
            for(int j = 0; j < n; ++j) if(!val[i][j]) dfs(i, j, ++cnt);
        printf("Case %d:\n", kase);
        //print(val);
        solver.init(9 * 9 * 4);
        for(int r = 0; r < n; ++r)
            for(int c = 0; c < n; ++c)
                for(int i = 0; i < 4; ++i) mat[r][c] &= ~fp[i];
        //print(mat);
        for(int r = 0; r < n; ++r) for(int c = 0; c < n; ++c) for(int v = 0; v < n; ++v) {
            if(!mat[r][c] || mat[r][c] == 1 + v) {
                vector<int> func;
                func.push_back(encode(SLOT, r, c));
                func.push_back(encode(ROW, r, v));
                func.push_back(encode(COL, c, v));
                func.push_back(encode(SUB, val[r][c] - 1, v));
                solver.add_row(encode(r, c, v), func);
            }
        }
        vector<int> ans;
        int res = solver.solve(ans);
        if(res == 0) puts("No solution");
        if(res == 1) {
            int r, c, v;
            for(size_t i = 0; i < ans.size(); ++i) {
                decode(ans[i], r, c, v);
                mat[r][c] = 1 + v;
            }
            print(mat);
        }
        if(res == 2) puts("Multiple Solutions");
    }
}
