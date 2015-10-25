#include <cstdio>
#include <iostream>
#include <algorithm>
#include <cstring>
using namespace std;
typedef long long LL;

const int MAXN = 1005;

int pos[MAXN];
int r, n;

int main() {
    while(scanf("%d%d", &r, &n) != EOF) {
        if(r == -1 && n == -1) break;
        for(int i = 0; i < n; ++i) scanf("%d", &pos[i]);
        sort(pos, pos + n);
        int res = 0, i = 0;
        while(i < n) {
            int j = i;
            while(j + 1 < n && pos[j + 1] - pos[i] <= r)
                ++j;
            res++;
            i = j;
            while(i < n && pos[i] - pos[j] <= r) ++i;
        }
        printf("%d\n", res);
    }
}
