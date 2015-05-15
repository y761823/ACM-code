/*
ID: y7618231
PROG: prime3
LANG: C++11
*/
#ifdef OYK_JUDGE
#define longformat "%I64d"
#else
#define longformat "%lld"
#endif // OYK_JUDGE

#include <cstdio>
#include <algorithm>
#include <cstring>
#include <iostream>
#include <cmath>
#include <vector>
#include <string>
using namespace std;

typedef long long LL;
#define REP(i, n) for(int i = 0; i < n; ++i)
#define FOR(i, s, t) for(int i = s; i <= t; ++i)

const int MAXN = 100010;
const int INF = 0x3f3f3f3f;

bool isprime[MAXN];
void init_prime(int n = 100000) {
    memset(isprime, true, sizeof(isprime));
    for(int i = 2; i * i <= n; ++i) {
        if(!isprime[i]) continue;
        for(int j = i * i; j <= n; j += i) isprime[j] = false;
    }
}

int order[5][5] = {
    {0, 20, 22, 23, 8},
    {13, 1, 17, 7, 15},
    {9, 10, 2, 11, 12},
    {14, 6, 18, 3, 16},
    {5, 19, 21, 24, 4}
};
bool row_flag[5][5] = {
    {0, 0, 0, 1, 0},
    {0, 0, 1, 0, 0},
    {0, 0, 0, 0, 1},
    {0, 0, 1, 0, 0},
    {0, 0, 0, 1, 0}
};
bool col_flag[5][5] = {
    {0, 1, 1, 0, 0},
    {0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0},
    {1, 0, 0, 0, 1},
    {0, 0, 0, 1, 0}
};
bool left_flag[5][5] = {
    {0, 0, 0, 0, 1},
    {0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0}
};
bool right_flag[5][5] = {
    {0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0},
    {0, 0, 0, 0, 1}
};

void get_order(int id, int &r, int &c) {
    for(r = 0; r < 5; ++r) for(c = 0; c < 5; ++c)
        if(order[r][c] == id) return ;
}

int row[25], col[25];
void init_order() {
    for(int i = 0; i < 25; ++i)
        get_order(i, row[i], col[i]);
}

int mat[5][5], sum;

int get(int r, int c, int fr, int fc) {
    int res = 0, cnt = 5;
    while(cnt--) {
        res += mat[r][c];
        r += fr, c += fc;
    }
    return res;
}
int get_row(int r) {
    return sum - get(r, 0, 0, 1);
}
int get_col(int c) {
    return sum - get(0, c, 1, 0);
}
int get_left() {
    return sum - get(4, 0, -1, 1);
}
int get_right() {
    return sum - get(0, 0, 1, 1);
}
int get_judge(int r, int c) {
    if(row_flag[r][c]) return get_row(r);
    if(col_flag[r][c]) return get_col(c);
    if(left_flag[r][c]) return get_left();
    if(right_flag[r][c]) return get_right();
    return INF;
}

bool judge(int r, int c, int fr, int fc) {
    int res = 0, cnt = 5, k = get(r, c, fr, fc);
    while(cnt--) {
        res = res * 10 + mat[r][c];
        r += fr, c += fc;
    }
    return isprime[res] && k == sum;
}
bool judge_row(int r) {
    return judge(r, 0, 0, 1);
}
bool judge_col(int c) {
    return judge(0, c, 1, 0);
}
bool judge_left() {
    return judge(4, 0, -1, 1);
}
bool judge_right() {
    return judge(0, 0, 1, 1);
}
bool judge(int r, int c) {
    bool flag = true;
    if(flag && row_flag[r][c]) flag = judge_row(r);
    if(flag && col_flag[r][c]) flag = judge_col(c);
    if(flag && left_flag[r][c]) flag = judge_left();
    if(flag && right_flag[r][c]) flag = judge_right();
    return flag;
}

vector<string> ans;

void push() {
    string s;
    for(int i = 0; i < 5; ++i)
        for(int j = 0; j < 5; ++j) s.push_back(mat[i][j] + '0');
    ans.push_back(s);
}

void dfs(int dep) {
    if(dep == 25) return push();
    int r = row[dep], c = col[dep], v = get_judge(r, c);
    if(get_row(r) > sum || get_col(c) > sum) return ;
    if(v != INF) {
        if(v < 0 || v > 9) return ;
        if((r == 0 || c == 0) && v == 0) return ;
        mat[r][c] = v;
        //printf("%d %d %d\n", r, c, v);
        if(judge(r, c)) dfs(dep + 1);
        mat[r][c] = 0;
        return ;
    }
    int st = (r == 0 || c == 0) ? 1 : 0;
    for(int i = st; i <= 9; ++i) {
        mat[r][c] = i;
        if(judge(r, c)) dfs(dep + 1);
        mat[r][c] = 0;
    }
}

void print_ans() {
    sort(ans.begin(), ans.end());
    bool flag = false;
    for(string &s : ans) {
        if(flag) puts("");
        else flag = true;
        for(int i = 0; i < 5; ++i) puts(s.substr(i * 5, 5).c_str());
    }
}

int main() {
#ifndef OYK_JUDGE
    freopen("prime3.in", "r", stdin); freopen("prime3.out", "w", stdout);
#endif // OYK_JUDGE
    init_prime();
    init_order();
    scanf("%d%d", &sum, &mat[0][0]);
    dfs(1);
    if(ans.size() == 0) puts("NONE");
    else print_ans();
}
