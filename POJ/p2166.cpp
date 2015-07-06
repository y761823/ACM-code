//C++ 375MS, G++ TLE
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;
typedef long long LL;

const int MAXN = 50010;

int heap[MAXN];

int main() {
    int n;
    while(scanf("%d", &n) != EOF) {
        heap[1] = 1;
        for(int i = 2; i <= n; ++i) {
            for(int j = i - 1; j != 1; j >>= 1) {
                heap[j] = heap[j >> 1];
            }
            heap[1] = i;
            heap[i] = 1;
        }
        for(int i = 1; i < n; ++i) printf("%d ", heap[i]);
        printf("%d\n", heap[n]);
    }
}
