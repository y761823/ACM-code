#include <cstdio>
#include <algorithm>
#include <iostream>
#include <cstring>
#include <vector>
using namespace std;
typedef long long LL;

const int MAXN = 22;
const int INF = 0x3f3f3f3f;

char s[MAXN];
int n, t, sum, sum11;

void add(int val) {
    int cnt = (val == 0), tmp = val;
    while(val > 0) {
        sum += (val % 10);
        val /= 10;
        cnt++;
    }
    while(cnt--) sum11 *= 10;
    sum11 = (sum11 + tmp) % 11;
}

int main() {
    int kase = 0;
    while(scanf("%d%d", &n, &t) != EOF) {
        if(n == -1 && t == -1) break;
        sum = sum11 = 0;
        add(n);
        for(int i = 0; i < t; ++i)
            add(sum);
        printf("Case #%d: %s\n", ++kase, sum11 == 0 ? "Yes" : "No");
    }
}
