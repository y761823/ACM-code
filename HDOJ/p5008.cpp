////////////////////System Comment////////////////////
////Welcome to Hangzhou Dianzi University Online Judge
////http://acm.hdu.edu.cn
//////////////////////////////////////////////////////
////Username: y761823
////Nickname: Oyk
////Run ID: 
////Submit time: 2014-09-14 18:37:25
////Compiler: GUN C++
//////////////////////////////////////////////////////
////Problem ID: 5008
////Problem Title: 
////Run result: Accept
////Run time:734MS
////Run memory:15528KB
//////////////////System Comment End//////////////////
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;
typedef long long LL;

const int MAXN = 100010;

char s[MAXN];
int sa[MAXN], rank[MAXN], c[MAXN], tmp[MAXN], height[MAXN];
int n, q, l, r, T;
LL k, v;

void makesa(int n, int m) {
    memset(c, 0, m * sizeof(int));
    for(int i = 0; i < n; ++i) ++c[rank[i] = s[i]];
    for(int i = 1; i < m; ++i) c[i] += c[i - 1];
    for(int i = 0; i < n; ++i) sa[--c[rank[i]]] = i;
    for(int k = 1; k < n; k <<= 1) {
        for(int i = 0; i < n; ++i) {
            int j = sa[i] - k;
            if(j < 0) j += n;
            tmp[c[rank[j]]++] = j;
        }
        int j = c[0] = sa[tmp[0]] = 0;
        for(int i = 1; i < n; ++i) {
            if(rank[tmp[i]] != rank[tmp[i - 1]] || rank[tmp[i] + k] != rank[tmp[i - 1] + k])
                c[++j] = i;
            sa[tmp[i]] = j;
        }
        memcpy(rank, sa, n * sizeof(int));
        memcpy(sa, tmp, n * sizeof(int));
    }
}

void calheight(int n) {
    for(int i = 0, k = 0; i < n; height[rank[i++]] = k) {
        k -= (k > 0);
        int j = sa[rank[i] - 1];
        while(s[i + k] == s[j + k]) ++k;
    }
}

LL sum[MAXN];

void get_sum() {
    sum[0] = 0;
    for(int i = 1; i <= n; ++i)
        sum[i] = sum[i - 1] + n - sa[i] - height[i];
}

int logn[MAXN];
void init(int n = 100000) {
    static bool done = false;
    if(done) return ;
    logn[0] = -1;
    for(int i = 1; i <= n; ++i)
        logn[i] = logn[i - 1] + ((i & (i - 1)) == 0);
    done = true;
}

struct RMQ {
    int best[20][MAXN];

    void initRMQ(int n, int val[]) {
        init();
        for(int i = 1; i <= n; ++i) best[0][i] = val[i];
        for(int i = 1; i <= logn[n]; ++i) {
            int ed = n - (1 << i) + 1;
            for(int j = 1; j <= ed; ++j)
                best[i][j] = min(best[i - 1][j], best[i - 1][j + (1 << (i - 1))]);
        }
    }

    int rmq(int a, int b) {
        int t = logn[b - a + 1];
        return min(best[t][a], best[t][b - (1 << t) + 1]);
    }

    int lcp(int a, int b) {
        if(a == b) return n;
        if(a > b) swap(a, b);
        ++a;
        return rmq(a, b);
    }
} height_rmq, sa_rmq;


int ans_pos, ans_len;

void get_ans() {
    int ansl, ansr;
    int a = 1, b = rank[ans_pos];
    while(a < b) {
        int mid = (a + b) >> 1;
        if(height_rmq.lcp(mid, rank[ans_pos]) < ans_len) a = mid + 1;
        else b = mid;
    }
    ansl = a;

    a = rank[ans_pos], b = n + 1;
    while(a < b) {
        int mid = (a + b) >> 1;
        //cout<<height_rmq.lcp(mid, rank[ans_pos])<<endl;
        if(height_rmq.lcp(mid, rank[ans_pos]) >= ans_len) a = mid + 1;
        else b = mid;
    }
    ansr = a - 1;

    ans_pos = sa_rmq.rmq(ansl, ansr);
}

void solve() {
    l = r = 0;
    if(k > sum[n]) return ;
    int a = 0, b = n;
    while(a < b) {
        int mid = (a + b) >> 1;
        if(sum[mid] < k) a = mid + 1;
        else b = mid;
    }
    ans_pos = sa[a];
    ans_len = k - sum[a - 1] + height[a];
    get_ans();
    l = ans_pos + 1;
    r = ans_pos + ans_len;
}

int main() {
    while(scanf("%s", s) != EOF) {
        n = strlen(s);
        makesa(n + 1, 128);
        calheight(n);
        height_rmq.initRMQ(n, height);
        sa_rmq.initRMQ(n, sa);
        get_sum();
        scanf("%d", &q);
        l = r = 0;
        while(q--) {
            scanf("%I64d", &v);
            k = (l ^ r ^ v) + 1;
            //printf("The Rank is %I64d\n", k);
            solve();
            printf("%d %d\n", l, r);
        }
    }
}