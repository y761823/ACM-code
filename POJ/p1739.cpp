#include <cstdio>
#include <iostream>
#include <algorithm>
#include <cstring>
using namespace std;
typedef long long LL;

const int MAXN = 12;
const int SIZEH = 13131;
const int MAXH = 20010;

struct hash_map {
    int head[SIZEH], size;
    int state[MAXH], next[MAXH];
    LL val[MAXH];

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

hash_map *cur, *last;
int acc[] = {0, -1, 1, 0};
char mat[MAXN][MAXN];
int n, m, en, em;

int getB(int state, int i) {
    return (state >> (i << 1)) & 3;
}

void setB(int &state, int i, int val) {
    state = (state & ~(3 << (i << 1))) | (val << (i << 1));
}

int getLB(int state, int i) {
    int ret = i, cnt = 1;
    while(cnt) {
        --ret;
        cnt += acc[getB(state, ret)];
    }
    return ret;
}

int getRB(int state, int i) {
    int ret = i, cnt = -1;
    while(cnt) {
        ++ret;
        cnt += acc[getB(state, ret)];
    }
    return ret;
}

void update(int x, int y, int state, LL tv) {
    int left = getB(state, y);
    int up = getB(state, y + 1);
    if(mat[x][y] == '#') {
        if(left == 0 && up == 0) cur->insert(state, tv);
        return ;
    }
    if(left == 0 && up == 0) {
        if(x == n - 1 || y == m - 1) return ;
        int newState = state;
        setB(newState, y, 1);
        setB(newState, y + 1, 2);
        cur->insert(newState, tv);
    } else if(left == 0 || up == 0) {
        if(x < n - 1) {
            int newState = state;
            setB(newState, y, up + left);
            setB(newState, y + 1, 0);
            cur->insert(newState, tv);
        }
        if(y < m - 1) {
            int newState = state;
            setB(newState, y, 0);
            setB(newState, y + 1, up + left);
            cur->insert(newState, tv);
        }
    } else {
        int newState = state;
        setB(newState, y, 0);
        setB(newState, y + 1, 0);
        if(left == 1 && up == 1) setB(newState, getRB(state, y + 1), 1);
        if(left == 1 && up == 2 && !(x == en && y == em)) return ;
        if(left == 2 && up == 2) setB(newState, getLB(state, y), 2);
        cur->insert(newState, tv);
    }
}

void findend() {
    for(en = n - 1; en >= 0; --en)
        for(em = m - 1; em >= 0; --em) if(mat[en][em] != '#') return ;
}

LL solve() {
    findend();
    cur = hashmap, last = hashmap + 1;
    last->init();
    last->insert(0, 1);
    for(int i = 0; i < n; ++i) {
        int sz = last->size;
        for(int k = 0; k < sz; ++k) last->state[k] <<= 2;
        for(int j = 0; j < m; ++j) {
            cur->init();
            sz = last->size;
            for(int k = 0; k < sz; ++k)
                update(i, j, last->state[k], last->val[k]);
            swap(cur, last);
        }
    }
    for(int k = 0; k < last->size; ++k)
        if(last->state[k] == 0) return last->val[k];
    return 0;
}

int main() {
    while(scanf("%d%d", &n, &m) != EOF) {
        if(n == 0 && m == 0) break;
        memset(mat, 0, sizeof(mat));
        for(int i = 0; i < n; ++i) scanf("%s", mat[i]);
        for(int i = 1; i < m - 1; ++i) mat[n][i] = '#';
        n += 2;
        cout<<solve()<<endl;
    }
}
