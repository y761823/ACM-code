/*
ID: y7618231
PROG: betsy
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
using namespace std;
typedef long long LL;
#define REP(i, n) for(int i = 0; i < n; ++i)
#define FOR(i, s, t) for(int i = s; i <= t; ++i)

const int MAXS = 20010;
const int SIZE = 13131;

struct Hashmap {
    int head[SIZE], ecnt;
    int next[MAXS], state[MAXS], val[MAXS];

    void init() {
        memset(head, -1, sizeof(head));
        ecnt = 0;
    }

    void insert(int st, int v) {
        int h = st % SIZE;
        for(int p = head[h]; ~p; p = next[p]) {
            if(state[p] == st) {
                val[p] += v;
                return ;
            }
        }
        state[ecnt] = st; val[ecnt] = v; next[ecnt] = head[h]; head[h] = ecnt++;
    }
} hashmap[2];

Hashmap *pre, *cur;
int acc[] = {0, -1, 1, 0};

int n, m;

int getB(int state, int i) {
    i <<= 1;
    return (state >> i) & 3;
}

int getLB(int state, int i) {
    int res = i, cnt = 1;
    while(cnt) cnt += acc[getB(state, --res)];
    return res;
}

int getRB(int state, int i) {
    int res = i, cnt = -1;
    while(cnt) cnt += acc[getB(state, ++res)];
    return res;
}

void setB(int &state, int i, int val) {
    i <<= 1;
    state = (state & ~(3 << i)) | (val << i);
}

void update(int x, int y, int state, int val) {
    int left = getB(state, y), up = getB(state, y + 1);
    if(left == 0 && up == 0) {
        if(x == n - 1 || y == m - 1) return ;
        int newState = state;
        setB(newState, y, 1);
        setB(newState, y + 1, 2);
        cur->insert(newState, val);
    } else if(left == 0 || up == 0) {
        if(x < n - 1) {
            int newState = state;
            setB(newState, y, left + up);
            setB(newState, y + 1, 0);
            cur->insert(newState, val);
        }
        if(y < m - 1) {
            int newState = state;
            setB(newState, y, 0);
            setB(newState, y + 1, left + up);
            cur->insert(newState, val);
        }
    } else {
        int newState = state;
        setB(newState, y, 0);
        setB(newState, y + 1, 0);
        if(left == 1 && up == 1) setB(newState, getRB(state, y + 1), 1);
        if(left == 1 && up == 2 && !(x == n - 1 && y == m - 1)) return ;
        if(left == 2 && up == 2) setB(newState, getLB(state, y), 2);
        cur->insert(newState, val);
    }
}

int solve() {
    pre = &hashmap[0], cur = &hashmap[1];
    int beg = 0;
    setB(beg, 0, 1);
    setB(beg, m - 1, 2);
    pre->init();
    pre->insert(beg, 1);
    for(int i = 1; i < n; ++i) {
        for(int k = 0; k < pre->ecnt; ++k) pre->state[k] <<= 2;
        for(int j = 0; j < m; ++j) {
            cur->init();
            for(int k = 0; k < pre->ecnt; ++k)
                update(i, j, pre->state[k], pre->val[k]);
            swap(cur, pre);
        }
    }
    return pre->val[0];
}

int main() {
#ifndef OYK_JUDGE
    freopen("betsy.in", "r", stdin); freopen("betsy.out", "w", stdout);
#endif // OYK_JUDGE
    scanf("%d", &m);
    n = m + 1;
    printf("%d\n", m == 1 ? 1 : solve());
}
