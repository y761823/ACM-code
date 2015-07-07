////////////////////System Comment////////////////////
////Welcome to Hangzhou Dianzi University Online Judge
////http://acm.hdu.edu.cn
//////////////////////////////////////////////////////
////Username: y761823
////Nickname: Oyk
////Run ID: 
////Submit time: 2014-10-16 16:35:10
////Compiler: GUN C++
//////////////////////////////////////////////////////
////Problem ID: 5030
////Problem Title: 
////Run result: Accept
////Run time:765MS
////Run memory:2728KB
//////////////////System Comment End//////////////////
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;
typedef long long LL;

const int MAXN = 100010;

char s[MAXN];
int sa[MAXN], tmp[MAXN], rank[MAXN], height[MAXN], c[MAXN];
int n, k;

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

int link[MAXN];

bool check(int pos, int len) {
    memset(link, -1, n * sizeof(int));
    int now_lcp = len;
    if(pos + len != n) link[pos] = pos + len - 1;
    for(int i = rank[pos] + 1; i <= n; ++i) {
        now_lcp = min(now_lcp, height[i]);
        int a = sa[i], b = sa[i] + now_lcp - 1;
        if(a > b) return false;
        link[a] = b;
    }

    int res = 0, minlink = n + 1;
    for(int i = 0; i < n; ++i) {
        if(link[i] != -1) minlink = min(minlink, link[i]);
        if(i == minlink) {
            res++;
            minlink = n + 1;
        }
    }
    return res < k;
}

void solve() {
    int l = 1, r = n;
    while(l < r) {
        int mid = (l + r) >> 1;
        if(check(sa[mid], n - sa[mid])) r = mid;
        else l = mid + 1;
    }

    int pos = sa[l];
    l = 1, r = n - pos;
    while(l < r) {
        int mid = (l + r) >> 1;
        if(check(pos, mid)) r = mid;
        else l = mid + 1;
    }

    int len = l;
    for(int i = pos; i < pos + len; ++i)
        putchar(s[i]);
    puts("");
}

int main() {
    while(scanf("%d", &k) != EOF && k) {
        scanf("%s", s);
        n = strlen(s);
        makesa(n + 1, 128);
        calheight(n);
        solve();
    }
}
