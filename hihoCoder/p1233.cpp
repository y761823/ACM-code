#include <cstdio>
#include <iostream>
#include <algorithm>
#include <cstring>
#include <map>
#include <queue>
using namespace std;

const double EPS = 1e-10;
const int INF = 0x3f3f3f3f;

int aaa[7] = {0, 1, 2, 3, 4, 5, 6};
int a[8];
int n, gold, T;

int encode(int a[]) {
    int res = 0;
    for(int i = 0; i < n; ++i)
        res = (res << 3) | a[i];
    return res;
}

void decode(int a[], int code) {
    for(int i = n - 1; i >= 0; --i) {
        a[i] = code & 7;
        code >>= 3;
    }
}

void normal(int a[]) {
    static int b[8], c[8];
    for(int i = 0; i < n; ++i) b[i] = i;
    gold = encode(b);
    sort(b, b + n, [=](int x, int y) {
         return a[x] < a[y];
    });
    for(int i = 0; i < n; ++i) c[b[i]] = i;
    for(int i = 0; i < n; ++i) a[c[i]] = i;
}

int getmin(int pos, int n) {
    for(int i = 0; i < n; ++i)
        if(a[i] == pos) return i;
    return INF;
}

bool canmove(int x) {
    for(int i = 0; i < x; ++i)
        if(a[i] == a[x]) return false;
    return true;
}

void print(int a[], int d = -1) {
    printf("#debug ");
    for(int i = 0; i < n; ++i)
        printf("%d ", a[i]);
    printf("%d\n", d);
}

int dis[7][1800000];
int que[1800000];

int f[] = {-1, 1};

void solve(int dis[]) {
    int l = 0, r = 0;
    dis[que[r++] = encode(aaa)] = 0;
    while(l != r) {
        int u = que[l++];
        int d = dis[u];
        //if(d >= 25) break;
        decode(a, u);
        //print(a, d);
        for(int i = 0; i < n; ++i) if(canmove(i)) {
            for(int v : f) {
                if(a[i] + v >= 0 && a[i] + v < n && getmin(a[i] + v, i) > i) {
                    a[i] += v;
                    int code = encode(a);
                    if(dis[code] == -1) {
                        dis[code] = d + 1;
                        que[r++] = code;
                    }
                    a[i] -= v;
                }
            }
        }
    }
}

int main() {
    memset(dis, -1, sizeof(dis));
    for(int i = 0; i < 7; ++i) {
        n = i + 1;
        solve(dis[i]);
    }
    scanf("%d", &T);
    while(T--) {
        scanf("%d", &n);
        for(int i = 0; i < n; ++i) scanf("%d", &a[i]);
        normal(a);
        printf("%d\n", dis[n - 1][encode(a)]);
    }
}
