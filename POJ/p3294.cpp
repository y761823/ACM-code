#include <cstdio>
#include <algorithm>
#include <iostream>
#include <cstring>
using namespace std;

const int MAXN = 110000;

char str[MAXN];
int s[MAXN], id[MAXN];
int sa[MAXN], rank[MAXN], height[MAXN], c[MAXN], tmp[MAXN];
int n, m, k;

void makesa(int m) {
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

void calheight() {
    for(int i = 0, k = 0; i < n; height[rank[i++]] = k) {
        k -= (k > 0);
        int j = sa[rank[i] - 1];
        while(s[i + k] == s[j + k]) ++k;
    }
}

int exist[MAXN];
int stk[MAXN];
int ans[MAXN];

bool cmp(int a, int b) {
    return rank[a] < rank[b];
}

void print(int L) {
    memset(exist, 0, m * sizeof(int));
    int sum = 1, top = 0, cnt = 0;
    stk[++top] = id[sa[0]];
    ++exist[id[sa[0]]];
    height[n] = 0;
    for(int i = 1; i < n; ++i) {
        if(height[i] >= L) {
            if(++exist[id[sa[i]]] == 1) ++sum;
            stk[++top] = id[sa[i]];
            if(sum > k && height[i + 1] < L) ans[cnt++] = sa[i];
        } else {
            while(top) --exist[stk[top--]];
            sum = ++exist[id[sa[i]]];
            stk[++top] = id[sa[i]];
        }
    }
    sort(ans, ans + cnt, cmp);
    for(int i = 0; i < cnt; ++i) {
        for(int j = ans[i]; j < ans[i] + L; ++j) putchar(str[j]);
        puts("");
    }
}

bool check(int L) {
    memset(exist, 0, m * sizeof(int));
    int sum = 1, top = 0;
    stk[++top] = id[sa[0]];
    ++exist[id[sa[0]]];
    for(int i = 1; i < n; ++i) {
        if(height[i] >= L) {
            if(++exist[id[sa[i]]] == 1) ++sum;
            stk[++top] = id[sa[i]];
            if(sum > k) return true;
        } else {
            while(top) --exist[stk[top--]];
            sum = ++exist[id[sa[i]]];
            stk[++top] = id[sa[i]];
        }
    }
    return false;
}

int solve() {
    int l = 1, r = 1001;
    while(l < r) {
        int mid = (l + r) >> 1;
        if(check(mid)) l = mid + 1;
        else r = mid;
    }
    return l - 1;
}
//n = 1
int main() {
    bool flag = false;
    while(scanf("%d", &m) != EOF && m) {
        k = m / 2;
        n = 0;
        for(int i = 0; i < m; ++i) {
            scanf("%s", str + n);
            while(str[n]) {
                id[n] = i;
                s[n] = str[n] - 'a' + 1;
                ++n;
            }
            s[n++] = i + 100;
        }
        s[n - 1] = 0;
        if(flag) puts("");
        else flag = true;
        if(m == 1) {
            puts(str);
            continue;
        }
        makesa(222);
        calheight();
        int t = solve();
        if(t) print(t);
        else puts("?");
    }
}
