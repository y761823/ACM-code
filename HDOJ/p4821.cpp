////////////////////System Comment////////////////////
////Welcome to Hangzhou Dianzi University Online Judge
////http://acm.hdu.edu.cn
//////////////////////////////////////////////////////
////Username: y761823
////Nickname: Oyk
////Run ID: 
////Submit time: 2014-08-07 23:17:58
////Compiler: GUN C++
//////////////////////////////////////////////////////
////Problem ID: 4821
////Problem Title: 
////Run result: Accept
////Run time:125MS
////Run memory:2640KB
//////////////////System Comment End//////////////////
#include <cstdio>
#include <iostream>
#include <cstring>
#include <algorithm>
#include <numeric>
using namespace std;
typedef long long LL;

const int MAXN = 100010;
const int MOD = 1e9+7;
const LL seed = 131;

char s[MAXN];
LL base[MAXN];
int tmp[MAXN], hash[MAXN];
int n, m, l;

const int SIZEH = 116969;
struct Hashmap {
    int stk[SIZEH], top;
    int head[SIZEH], ecnt;
    int next[SIZEH], val[SIZEH], cnt[SIZEH];

    Hashmap() {
        memset(head, -1, sizeof(head));
    }

    void init() {
        while(top) head[stk[--top]] = -1;
        ecnt = 0;
    }

    int insert(int st) {
        int h = st % SIZEH;
        for(int p = head[h]; ~p; p = next[p]) {
            if(val[p] == st) return ++cnt[p];
        }
        stk[top++] = h;
        val[ecnt] = st; cnt[ecnt] = 1; next[ecnt] = head[h]; head[h] = ecnt++;
        return 1;
    }

    int remove(int st) {
        int h = st % SIZEH;
        for(int p = head[h]; ~p; p = next[p]) {
            if(val[p] == st) return --cnt[p];
        }
        return 0;
    }
} hashmap;

void init(int n = 100000) {
    base[0] = 1;
    for(int i = 1; i <= n; ++i) base[i] = base[i - 1] * seed % MOD;
}

void inithash() {
    tmp[0] = s[0];
    for(int i = 1; i < n; ++i) tmp[i] = (tmp[i - 1] * seed + s[i]) % MOD;
    hash[0] = tmp[m - 1];
    for(int i = 1; i + m - 1 < n; ++i)
        hash[i] = (tmp[i + m - 1] - tmp[i - 1] * base[m] % MOD + MOD) % MOD;
}

int solve() {
    inithash();
    int res = 0;
    for(int beg = 0; beg < m; ++beg) {
        hashmap.init();
        int cnt = 0;
        for(int i = beg, t = 1; i + m - 1 < n; i += m, ++t) {
            if(t > l) cnt -= (hashmap.remove(hash[i - m * l]) == 1);
            cnt += (hashmap.insert(hash[i]) == 2);
            if(t >= l) res += (cnt == 0);
        }
    }
    return res;
}

int main() {
    init();
    while(scanf("%d%d", &l, &m) != EOF) {
        scanf("%s", s);
        n = strlen(s);
        printf("%d\n", solve());
    }
}
