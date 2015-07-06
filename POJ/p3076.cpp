#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;

const int MAXC = 1024 + 10;
const int MAXR = 4096 + 10;
const int MAXP = MAXR * 4 + MAXC;

struct DLX {
    int n, sz;//列数，结点总数
    int sum[MAXC];//每列拥有的结点数
    int row[MAXP], col[MAXP];//结点所在的行和列
    int left[MAXP], right[MAXP], up[MAXP], down[MAXP];//十字链表
    int ansd, ans[MAXR];

    void init(int nn) {
        n = nn;
        for(int i = 0; i <= n; ++i) {
            up[i] = down[i] = i;
            left[i] = i - 1; right[i] = i + 1;
        }
        right[n] = 0; left[0] = n;
        sz = n + 1;
        memset(sum, 0, sizeof(sum));
    }

    void add_row(int r, vector<int> &columns) {
        int first = sz;
        for(int i = 0, len = columns.size(); i < len; ++i) {
            int c = columns[i];
            left[sz] = sz - 1; right[sz] = sz + 1; down[sz] = c; up[sz] = up[c];
            down[up[c]] = sz; up[c] = sz;
            row[sz] = r; col[sz] = c;
            ++sum[c]; ++sz;
        }
        right[sz - 1] = first; left[first] = sz - 1;
    }

    void remove(int c) {
        left[right[c]] = left[c];
        right[left[c]] = right[c];
        for(int i = up[c]; i != c; i = up[i])
            for(int j = right[i]; j != i; j = right[j]) {
                up[down[j]] = up[j]; down[up[j]] = down[j]; --sum[col[j]];
            }
    }

    void restore(int c) {
        for(int i = down[c]; i != c; i = down[i])
            for(int j = left[i]; j != i; j = left[j]) {
                up[down[j]] = j; down[up[j]] = j; ++sum[col[j]];
            }
        left[right[c]] = c;
        right[left[c]] = c;
    }

    bool dfs(int d) {
        if(right[0] == 0) {
            ansd = d;
            return true;
        }
        int c = right[0];
        for(int i = right[0]; i != 0; i = right[i]) if(sum[i] < sum[c]) c = i;
        remove(c);
        for(int i = down[c]; i != c; i = down[i]) {
            ans[d] = row[i];
            for(int j = left[i]; j != i; j = left[j]) remove(col[j]);
            if(dfs(d + 1)) return true;
            for(int j = right[i]; j != i; j = right[j]) restore(col[j]);
        }
        restore(c);
        return false;
    }

    bool solve(vector<int> &v) {
        v.clear();
        if(!dfs(0)) return false;
        for(int i = 0; i < ansd; ++i) v.push_back(ans[i]);
        return true;
    }
};

DLX solver;

const int SLOT = 0;
const int ROW = 1;
const int COL = 2;
const int SUB = 3;

inline int encode(int a, int b, int c) {
    return a * 256 + b * 16 + c + 1;
}

void decode(int code, int &a, int &b, int &c) {
    --code;
    c = code % 16; code /= 16;
    b = code % 16; code /= 16;
    a = code;
}

char puzzle[16][20];

bool read() {
    for(int i = 0; i < 16; ++i)
        if(scanf("%s", puzzle[i]) == EOF) return false;
    return true;
}

int main() {
    int kase = 0;
    while(read()) {
        if(++kase != 1) printf("\n");
        solver.init(1024);
        for(int r = 0; r < 16; ++r)
            for(int c = 0; c < 16; ++c)
                for(int v = 0; v < 16; ++v)
                    if(puzzle[r][c] == '-' || puzzle[r][c] == 'A' + v) {
                        vector<int> columns;
                        columns.push_back(encode(SLOT, r, c));
                        columns.push_back(encode(ROW, r, v));
                        columns.push_back(encode(COL, c, v));
                        columns.push_back(encode(SUB, (r/4)*4+c/4, v));
                        solver.add_row(encode(r, c, v), columns);
                    }
        vector<int> ans;
        solver.solve(ans);
        for(int i = 0, len = ans.size(); i < len; ++i) {
            int r, c, v;
            decode(ans[i], r, c, v);
            puzzle[r][c] = 'A' + v;
        }
        for(int i = 0; i < 16; ++i) printf("%s\n", puzzle[i]);
    }
}
