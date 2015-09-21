#include <cstdio>
#include <iostream>
#include <algorithm>
#include <cstring>
using namespace std;

const int MAXN = 1000010;
const int INF = 0x3f3f3f3f;

int lval[MAXN], lsum[MAXN], lmax[MAXN], rval[MAXN];
int ltop, rtop;
int n;

int add_left(int x) {
    lmax[ltop] = lsum[ltop] = lval[ltop] = x;
    if(ltop > 0) {
        lsum[ltop] += lsum[ltop - 1];
        lmax[ltop] = max(lmax[ltop - 1], lsum[ltop]);
    }
    ltop++;
}

void add_right(int x) {
    rval[rtop++] = x;
}

int main() {
    while(scanf("%d", &n) != EOF) {
        ltop = rtop = 0;
        char c; int x;
        for(int i = 0; i < n; ++i) {
            scanf(" %c", &c);
            if(c == 'I') {
                scanf("%d", &x);
                add_left(x);
            } else if(c == 'D') {
                ltop = max(ltop - 1, 0);
            } else if(c == 'L') {
                if(ltop) add_right(lval[--ltop]);
            } else if(c == 'R') {
                if(rtop) add_left(rval[--rtop]);
            } else if(c == 'Q') {
                scanf("%d", &x);
                printf("%d\n", lmax[x - 1]);
            }
        }
    }
}
