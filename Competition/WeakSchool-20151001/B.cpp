#include <cstdio>
#include <cstring>
#include <algorithm>
#include <iostream>
using namespace std;
typedef long long LL;

const int MAXN = 100010;
const double EPS = 1e-8;

int a[MAXN], b[MAXN];
int n;

LL solve() {
    LL res = 0;
    for(LL k = 10; ; k *= 10) {
        for(int i = 0; i < n; ++i) b[i] = a[i] % k;
        sort(b, b + n);
        if(b[n - 1] + b[n - 1] < k) break;
        for(int l = 0, r = n - 1; l < n; ++l) {
            while(r >= 0 && b[l] + b[r] >= k) --r;
            res += n - max(l + 1, r + 1);
        }
    }
    return res;
}

int main() {
    while(scanf("%d", &n) != EOF) {
        for(int i = 0; i < n; ++i)
            scanf("%d", &a[i]);
        cout<<solve()<<endl;
    }
}
