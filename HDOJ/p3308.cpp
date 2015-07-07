////////////////////System Comment////////////////////
////Welcome to Hangzhou Dianzi University Online Judge
////http://acm.hdu.edu.cn
//////////////////////////////////////////////////////
////Username: y761823
////Nickname: Oyk
////Run ID: 
////Submit time: 2014-05-02 17:08:46
////Compiler: GUN C++
//////////////////////////////////////////////////////
////Problem ID: 3308
////Problem Title: 
////Run result: Accept
////Run time:593MS
////Run memory:3784KB
//////////////////System Comment End//////////////////
#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

const int MAXN = 100010 << 2;

int lmax[MAXN], rmax[MAXN], mmax[MAXN];
int a[MAXN], n, m, T;

void update(int x, int l, int r, int pos, int val) {
    if(pos <= l && r <= pos) {
        a[pos] = val;
    } else {
        int ll = x << 1, rr = ll | 1, mid = (l + r) >> 1;
        if(pos <= mid) update(ll, l, mid, pos, val);
        if(mid < pos) update(rr, mid + 1, r, pos, val);
        if(a[mid] < a[mid + 1]) {
            lmax[x] = lmax[ll] + (lmax[ll] == mid - l + 1) * lmax[rr];
            rmax[x] = rmax[rr] + (rmax[rr] == r - mid) * rmax[ll];
            mmax[x] = max(rmax[ll] + lmax[rr], max(mmax[ll], mmax[rr]));
        } else {
            lmax[x] = lmax[ll];
            rmax[x] = rmax[rr];
            mmax[x] = max(mmax[ll], mmax[rr]);
        }
    }
}

int query(int x, int l, int r, int aa, int bb) {
    if(aa <= l && r <= bb) {
        return mmax[x];
    } else {
        int ll = x << 1, rr = ll | 1, mid = (l + r) >> 1;
        int ans = 0;
        if(aa <= mid) ans = max(ans, query(ll, l, mid, aa, bb));
        if(mid < bb) ans = max(ans, query(rr, mid + 1, r, aa, bb));
        if(a[mid] < a[mid + 1]) ans = max(ans, min(rmax[ll], mid - aa + 1) + min(lmax[rr], bb - mid));
        return ans;
    }
}

void build(int x, int l, int r) {
    if(l == r) {
        lmax[x] = rmax[x] = mmax[x] = 1;
    } else {
        int ll = x << 1, rr = ll | 1, mid = (l + r) >> 1;
        build(ll, l, mid);
        build(rr, mid + 1, r);
        if(a[mid] < a[mid + 1]) {
            lmax[x] = lmax[ll] + (lmax[ll] == mid - l + 1) * lmax[rr];
            rmax[x] = rmax[rr] + (rmax[rr] == r - mid) * rmax[ll];
            mmax[x] = max(rmax[ll] + lmax[rr], max(mmax[ll], mmax[rr]));
        } else {
            lmax[x] = lmax[ll];
            rmax[x] = rmax[rr];
            mmax[x] = max(mmax[ll], mmax[rr]);
        }
    }
}

int main() {
    scanf("%d", &T);
    while(T--) {
        scanf("%d%d", &n, &m);
        for(int i = 0; i < n; ++i) scanf("%d", &a[i]);
        build(1, 0, n - 1);
        while(m--) {
            char c;
            int a, b;
            scanf(" %c%d%d", &c, &a, &b);
            if(c == 'Q') printf("%d\n", query(1, 0, n - 1, a, b));
            else update(1, 0, n - 1, a, b);
        }
    }
}
