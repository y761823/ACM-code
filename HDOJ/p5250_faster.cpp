#include <cstdio>
#include <algorithm>
#include <iostream>
#include <cstring>
using namespace std;
typedef long long LL;

/*
              L|    R|
         B -> 37 38 39
              40 41 42
         F -> 43 44 45
U -> 28 29 30  1  2  3 10 11 12 19 20 21
     31 32 33  4  5  6 13 14 15 22 23 24
D -> 34 35 36  7  8  9 16 17 18 25 26 27
              46 47 48
              49 50 51
              52 53 54
*/

int cu[] = {28, 29, 30, 1, 2, 3, 10, 11, 12, 19, 20, 21};
int cd[] = {34, 35, 36, 7, 8, 9, 16, 17, 18, 25, 26 ,27};

int cu2[] = {37, 40, 0, 43, 44, 0, 45, 42, 0, 39, 38, 0};
int cd2[] = {52, 49, 0, 46, 47, 0, 48, 51, 0, 54, 53, 0};

int cr[] = {39, 42, 45, 3, 6, 9, 48, 51, 54, 25, 22, 19};
int cl[] = {37, 40, 43, 1, 4, 7, 46, 49, 52, 27, 24, 21};

int cr2[] = {10, 13, 0, 16, 17, 0, 18, 15, 0, 12, 11, 0};
int cl2[] = {28, 29, 0, 30, 33, 0, 36, 35, 0, 34, 31, 0};

int cf[] = {43, 44, 45, 10, 13, 16, 48, 47, 46, 36, 33, 30};
int cb[] = {37, 38, 39, 12, 15, 18, 54, 53, 52, 34, 31, 28};

int cf2[] = {1, 2, 0, 3, 6, 0, 9, 8, 0, 7, 4, 0};
int cb2[] = {19, 22, 0, 25, 26, 0, 27, 24, 0, 21, 20, 0};

void amendment() {
    reverse(cu, cu + 12); reverse(cu2, cu2 + 12);
    reverse(cr, cr + 12); reverse(cr2, cr2 + 12);
    reverse(cb, cb + 12); reverse(cb2, cb2 + 12);
}

char op[310];
int qun[55], tmp[55];
int T;

void change(int c[]) {
    memcpy(tmp, qun, sizeof(qun));
    for(int i = 8; i >= 0; --i) if(c[i]) {
        swap(qun[c[i]], qun[c[i + 3]]);
        //qun[find(tmp, tmp + 55, c[i]) - tmp] = c[(i + 3) % 12];
    }
}
void change(int c[], int c2[], int p) {
    while(p--) change(c), change(c2);
}
void change(int c[], int c2[], char *&s) {
    s++;
    if(*s == '\'') change(c, c2, 3), s++;
    else if(*s == '2') change(c, c2, 2), s++;
    else change(c, c2, 1);
}

void build() {
    for(int i = 1; i <= 54; ++i) qun[i] = i;
    char *s = op;
    while(*s) {
        if(*s == 'U') change(cu, cu2, s);
        if(*s == 'D') change(cd, cd2, s);
        if(*s == 'R') change(cr, cr2, s);
        if(*s == 'L') change(cl, cl2, s);
        if(*s == 'F') change(cf, cf2, s);
        if(*s == 'B') change(cb, cb2, s);
    }
}

bool vis[55];
int get_ans() {
    memset(vis, 0, sizeof(vis));
    int res = 1;
    for(int i = 1; i <= 54; ++i) if(!vis[i]) {
        int cnt = 0;
        for(int j = i; !vis[j]; j = qun[j])
            cnt++, vis[j] = true;
        res = res / __gcd(res, cnt) * cnt;
    }
    return res;
}

int main() {
    amendment();
    scanf("%d", &T);
    for(int t = 1; t <= T; ++t) {
        scanf("%s", op);
        build();
        printf("Case #%d:\n%d\n", t, get_ans());
    }
}
