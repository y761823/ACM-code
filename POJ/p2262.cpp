#include <cstdio>
#include <algorithm>
#include <cstring>
#include <algorithm>
#include <numeric>
using namespace std;

const int MAXN = 1000010;

bool isprime[MAXN];
int prime[MAXN], label[MAXN], total;
int n;

void makePrime(int n = 1000000) {
    for(int i = 2; i <= n; ++i) {
        if(!label[i]) {
            prime[total++] = i;
            label[i] = total;
        }
        for(int j = 0; j < label[i]; ++j) {
            if(i * prime[j] > n) break;
            label[i * prime[j]] = j + 1;
        }
    }
    for(int i = 0; i < total; ++i) isprime[prime[i]] = true;
}

int main() {
    makePrime();
    while(scanf("%d", &n) != EOF && n) {
        int res = 1;
        while(!isprime[n - prime[res]]) res++;
        printf("%d = %d + %d\n", n, prime[res], n - prime[res]);
    }
}
