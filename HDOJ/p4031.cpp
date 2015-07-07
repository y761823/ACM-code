////////////////////System Comment////////////////////
////Welcome to Hangzhou Dianzi University Online Judge
////http://acm.hdu.edu.cn
//////////////////////////////////////////////////////
////Username: y761823
////Nickname: Oyk
////Run ID: 
////Submit time: 2014-08-26 18:34:15
////Compiler: GUN C++
//////////////////////////////////////////////////////
////Problem ID: 4031
////Problem Title: 
////Run result: Accept
////Run time:1453MS
////Run memory:16144KB
//////////////////System Comment End//////////////////
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <cstring>
#include <vector>
using namespace std;

const int MAXN = 20010;
const int MAXT = MAXN << 2;
const int MAXP = 55;

struct Node {
    int pos, op, time;
    Node() {}
    Node(int pos, int op, int time): pos(pos), op(op), time(time) {}
    bool operator < (const Node &rhs) const {
        return pos < rhs.pos;
    }
};

vector<int> qtime[MAXN], qid[MAXN];
Node attack[MAXN * 2];
int ans[MAXN];
int T, n, q, t, ncnt, atime;

void init() {
    for(int i = 0; i <= n; ++i) qtime[i].clear(), qid[i].clear();
    memset(ans, -1, q * sizeof(int));
    ncnt = atime = 0;
}

#define ll (x << 1)
#define rr (ll | 1)
#define mid ((l + r) >> 1)
int atk[MAXT][MAXP], empty[MAXT][MAXP];
int cnt[MAXN];

void update(int x) {
    for(int i = 0; i < t; ++i) {
        int t = empty[ll][i];
        atk[x][i] = atk[ll][i] + atk[rr][t];
        empty[x][i] = empty[rr][t];
    }
}

void build(int x, int l, int r) {
    if(l == r) {
        atk[x][0] = empty[x][0] = cnt[l] = 0;
        for(int i = 1; i < t; ++i)
            atk[x][i] = 0, empty[x][i] = i - 1;
    } else {
        build(ll, l, mid);
        build(rr, mid + 1, r);
        update(x);
    }
}

void modify(int x, int l, int r, int a, int b) {
    if(a <= l && r <= b) {
        atk[x][0] = 0; empty[x][0] = cnt[a] ? t - 1 : 0;
        for(int i = 1; i < t; ++i)
            atk[x][i] = cnt[a], empty[x][i] = i - 1;
    } else {
        if(a <= mid) modify(ll, l, mid, a, b);
        if(mid < b) modify(rr, mid + 1, r, a, b);
        update(x);
    }
}

void modify(int pos) {
    modify(1, 1, atime, pos, pos);
}

int query(int x, int l, int r, int a, int b, int e) {
    if(a <= l && r <= b) {
        return atk[x][e];
    } else {
        int res = query(ll, l, mid, a, b, e);
        if(mid < b) res += query(rr, mid + 1, r, a, b, empty[ll][e]);
        return res;
    }
}

int query(int pos) {
    if(pos == 0) return 0;
    return query(1, 1, atime, 1, pos, 0);
}

char s[10];

int main() {
    scanf("%d", &T);
    for(int kase = 1; kase <= T; ++kase) {
        scanf("%d%d%d", &n, &q, &t);
        init();
        for(int i = 0, a, b; i < q; ++i) {
            scanf("%s", s);
            if(strcmp(s, "Attack") == 0) {
                scanf("%d%d", &a, &b);
                atime++;
                attack[ncnt++] = Node(a, 1, atime);
                attack[ncnt++] = Node(b + 1, -1, atime);
            } else {
                scanf("%d", &a);
                qtime[a].push_back(atime);
                qid[a].push_back(i);
            }
        }
        sort(attack, attack + ncnt);

        build(1, 1, atime);
        int p = 0;
        for(int i = 1; i <= n; ++i) {
            while(p < ncnt && attack[p].pos == i) {
                cnt[attack[p].time] += attack[p].op;
                modify(attack[p++].time);
            }
            for(size_t k = 0; k < qtime[i].size(); ++k)
                ans[qid[i][k]] = query(qtime[i][k]);
        }

        printf("Case %d:\n", kase);
        for(int i = 0; i < q; ++i)
            if(ans[i] != -1) printf("%d\n", ans[i]);
    }
}
