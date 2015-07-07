////////////////////System Comment////////////////////
////Welcome to Hangzhou Dianzi University Online Judge
////http://acm.hdu.edu.cn
//////////////////////////////////////////////////////
////Username: y761823
////Nickname: Oyk
////Run ID: 
////Submit time: 2014-08-30 21:54:57
////Compiler: GUN C++
//////////////////////////////////////////////////////
////Problem ID: 4064
////Problem Title: 
////Run result: Accept
////Run time:15MS
////Run memory:8224KB
//////////////////System Comment End//////////////////
#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>
using namespace std;
typedef long long LL;

const int MAXN = 13;
const int SIZE = 1000007;
const int MOD = 1e9 + 7;

struct Hashmap {
    int head[SIZE], ecnt;
    int to[SIZE], next[SIZE], val[SIZE];
    int stk[SIZE], top;

    Hashmap() {
        memset(head, -1, sizeof(head));
    }

    void clear() {
        while(top) head[stk[--top]] = -1;
        ecnt = 0;
        //for(int i = 0; i < SIZE; ++i) if(head[i] != -1) cout<<"error"<<endl;
    }

    void insert(int st, int value) {
        int h = st % SIZE;
        for(int p = head[h]; ~p; p = next[p]) {
            if(to[p] == st) {
                val[p] += value;
                if(val[p] >= MOD) val[p] -= MOD;
                return ;
            }
        }
        if(head[h] == -1) stk[top++] = h;
        to[ecnt] = st; val[ecnt] = value; next[ecnt] = head[h]; head[h] = ecnt++;
    }
} hashmap[2], *pre, *cur;

char s[MAXN][MAXN][5];
int w[128];
int n, m, T;

int getState(int state, int i) {
    return (state >> (i << 1)) & 3;
}

void setState(int &state, int i, int val) {
    i <<= 1;
    state = (state & ~(3 << i)) | (val << i);
}

int solve() {
    pre = &hashmap[0], cur = &hashmap[1];
    cur->clear();
    cur->insert(0, 1);
    int maxState = (1 << ((m + 1) << 1)) - 1;
    for(int i = 0; i < n; ++i) {
        for(int p = 0; p < cur->ecnt; ++p)
            cur->to[p] = (cur->to[p] << 2) & maxState;
        for(int j = 0; j < m; ++j) {
            swap(pre, cur);
            cur->clear();
            for(int p = 0; p < pre->ecnt; ++p) {
                int st = pre->to[p];
                for(int k = 0; k < 4; ++k) {
                    if(j != 0 && w[(int)s[i][j][(k + 1) & 3]] != getState(st, j)) continue;
                    if(i != 0 && w[(int)s[i][j][(k + 2) & 3]] != getState(st, j + 1)) continue;
                    int new_st = st;
                    setState(new_st, j, w[(int)s[i][j][k]]);
                    setState(new_st, j + 1, w[(int)s[i][j][(k + 3) & 3]]);
                    cur->insert(new_st, pre->val[p]);
                }
            }
        }
    }
    int res = 0;
    for(int p = 0; p < cur->ecnt; ++p) {
        res += cur->val[p];
        if(res >= MOD) res -= MOD;
    }
    return res;
}

int main() {
    w['F'] = 0; w['C'] = 1; w['R'] = 2;
    scanf("%d", &T);
    for(int t = 1; t <= T; ++t) {
        scanf("%d%d", &n, &m);
        for(int i = 0; i < n; ++i)
            for(int j = 0; j < m; ++j) scanf("%s", s[i][j]);
        printf("Case %d: %d\n", t, solve());
    }
}
