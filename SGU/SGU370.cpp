#include <bits/stdc++.h>
using namespace std;
typedef long long LL;

#define foreach(iter, v) for(__typeof(v.begin()) iter = v.begin(); iter != v.end(); ++iter)

const int MAXN = 1000010;

bool isprime[MAXN];
int mobius[MAXN], prime[MAXN];
int total;

void init(int n = 1000000) {
    memset(isprime, true, sizeof(isprime));
    mobius[1] = 1;
    for(int i = 2; i <= n; ++i) {
        if(isprime[i]) {
            prime[total++] = i;
            mobius[i] = -1;
        }
        for(int j = 0; j < total && i * prime[j] <= n; ++j) {
            isprime[i * prime[j]] = false;
            if(i % prime[j]) mobius[i * prime[j]] = -mobius[i];
            else {
                mobius[i * prime[j]] = 0;
                break;
            }
        }
    }
}

LL solve(int n, int m) {
    if(n == 1 && m == 1) return 0;
    if(n == 1 || m == 1) return 1;

    int p = min(--n, --m);
    init(p);

    LL res = 2;
    for(int i = 1; i <= p; ++i)
        res += (LL)mobius[i] * (n / i) * (m / i);
    return res;
}

int main() {
    int n, m;
    scanf("%d%d", &n, &m);
    cout<<solve(n, m)<<endl;
}
