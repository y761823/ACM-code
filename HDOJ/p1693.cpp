////////////////////System Comment////////////////////
////Welcome to Hangzhou Dianzi University Online Judge
////http://acm.hdu.edu.cn
//////////////////////////////////////////////////////
////Username: y761823
////Nickname: Oyk
////Run ID: 
////Submit time: 2013-10-29 17:25:14
////Compiler: GUN C++
//////////////////////////////////////////////////////
////Problem ID: 1693
////Problem Title: 
////Run result: Accept
////Run time:0MS
////Run memory:452KB
//////////////////System Comment End//////////////////
#include <iostream>
#include <algorithm>
#include <cstring>
#include <cstdio>
using namespace std;
typedef long long LL;

const int MAXH = 20010;
const int SIZEH = 13131;

struct hash_map {
    int head[SIZEH];
    int next[MAXH], state[MAXH];
    LL val[MAXH];
    int size;

    void init() {
        memset(head, -1, sizeof(head));
        size = 0;
    }

    void insert(int st, LL sv) {
        int h = st % SIZEH;
        for(int p = head[h]; ~p; p = next[p]) {
            if(state[p] == st) {
                val[p] += sv;
                return ;
            }
        }
        state[size] = st; val[size] = sv; next[size] = head[h]; head[h] = size++;
    }
} hashmap[2];

int getB(int state, int i) {
    return (state >> i) & 1;
}

void setB(int &state, int i, int val) {
    state = (state & ~(1 << i)) | (val << i);
}

int mat[14][14];
int n, m, T;
hash_map *cur, *last;

void update(int state, LL val, int x, int y) {
    int left = getB(state, y);
    int up = getB(state, y + 1);
    if(mat[x][y] == 0) {
        if(left == 0 && up == 0) cur->insert(state, val);
        return ;
    }
    if(left == 0 && up == 0) {
        if(x < n - 1 && y < m - 1) {
            int newState = state;
            setB(newState, y, 1);
            setB(newState, y + 1, 1);
            cur->insert(newState, val);
        }
    } else if(left == 0 || up == 0) {
        if(x < n - 1) {
            int newState = state;
            setB(newState, y, 1);
            setB(newState, y + 1, 0);
            cur->insert(newState, val);
        }
        if(y < m - 1) {
            int newState = state;
            setB(newState, y, 0);
            setB(newState, y + 1, 1);
            cur->insert(newState, val);
        }
    } else {
        int newState = state;
        setB(newState, y, 0);
        setB(newState, y + 1, 0);
        cur->insert(newState, val);
    }
}

LL solve() {
    cur = hashmap, last = hashmap + 1;
    last->init();
    last->insert(0, 1);
    for(int i = 0; i < n; ++i) {
        int sz = last->size;
        for(int k = 0; k < sz; ++k) last->state[k] <<= 1;
        for(int j = 0; j < m; ++j) {
            cur->init();
            sz = last->size;
            for(int k = 0; k < sz; ++k)
                update(last->state[k], last->val[k], i, j);
            swap(cur, last);
        }
    }
    for(int k = 0; k < last->size; ++k)
        if(last->state[k] == 0) return last->val[k];
    return 0;
}

int main() {
    scanf("%d", &T);
    for(int t = 1; t <= T; ++t) {
        scanf("%d%d", &n, &m);
        for(int i = 0; i < n; ++i)
            for(int j = 0; j < m; ++j) scanf("%d", &mat[i][j]);
        printf("Case %d: There are %I64d ways to eat the trees.\n", t, solve());
    }
}
