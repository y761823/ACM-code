#include <cstdio>
#include <iostream>
#include <algorithm>
#include <cstring>
#include <map>
using namespace std;
typedef long long LL;
#define REP(i, n) for(int i = 0; i < n; ++i)

const int MAXR = 130;
const int MAXC = 18;
const int MAXN = 100007;

int now[1 << 16], nxt[1 << 16];
char str[MAXR][MAXC];
int cnt[1 << 16], len[MAXR];
int r, c;

char getfront(int id, int bits) {
    if(!(bits & 1)) return ' ';
    return str[id][cnt[bits] - 1];
}

char getback(int id, int bits, int n) {
    n = (1 << (n - 1));
    if(!(bits & n)) return ' ';
    return str[id][len[id] - cnt[bits]];
}

void update_max(int &a, int b) {
    if(a < b) a = b;
}

int getfull(int n) {
    return (1 << n) - 1;
}

int solve() {
    int full = (1 << c) - 1;
    memset(now, -1, (1 << c) * sizeof(int));
    now[0] = 0;
    for(int x = 0; x < r; ++x) {
        for(int y = 0; y < c; ++y) {
            memset(nxt, -1, (1 << c) * sizeof(int));
            for(int state = 0; state < (1 << c); ++state) if(~now[state]) {
                if(c - y - 1 + cnt[state & getfull(y)] >= len[x]) {
                    int newstate = (state << 1) & full;
                    update_max(nxt[newstate], now[state]);
                }
                if(cnt[state & getfull(y)] < len[x]) {
                    int newstate = ((state << 1) & full) | 1;
                    int newval = now[state];
                    char ch = getfront(x, newstate & getfull(y + 1));
                    if(ch == getfront(x, state & getfull(y))) newval += 2;
                    if(ch == getback(x - 1, state >> y, c - y)) newval += 2;
                    update_max(nxt[newstate], newval);
                }
            }
            memcpy(now, nxt, (1 << c) * sizeof(int));
        }
    }

    return *max_element(now, now + (1 << c));
}

int main() {
    scanf("%d%d", &r, &c);
    for(int i = 0; i < r; ++i) {
        scanf("%s", str[i]);
        len[i] = strlen(str[i]);
    }

    for(int i = 1; i < (1 << c); ++i)
        cnt[i] = cnt[i >> 1] + (i & 1);
    printf("%d\n", solve());
}
