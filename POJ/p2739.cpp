#include <cstdio>
#include <algorithm>
#include <cstring>
#include <algorithm>
#include <numeric>
using namespace std;

const int MAXN = 10010;

int label[MAXN], prime[MAXN];
int n, total;
void makePrime(int n = 10000) {
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
}

int cnt[MAXN], sum[MAXN];
void getans(int n = 10000) {
    partial_sum(prime, prime + total, sum);
    for(int i = 0; i < total; ++i) {
        if(sum[i] <= n) cnt[sum[i]]++;
        for(int j = i + 1; j < total && sum[j] - sum[i] <= n; ++j)
            cnt[sum[j] - sum[i]]++;
    }
}

int main() {
    makePrime();
    getans();
    while(scanf("%d", &n) != EOF && n)
        printf("%d\n", cnt[n]);
}
