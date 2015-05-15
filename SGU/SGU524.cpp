#include <bits/stdc++.h>
using namespace std;
typedef long long LL;

const int MAXN = 410;

int a[MAXN], n;
double b[MAXN], ans[MAXN], mindis;

double get_dis(int a[], double b[]) {
    double res = 0;
    for(int i = 0; i < n; ++i) res += abs(a[i] - b[i]);
    return res;
}

int main() {
    scanf("%d", &n);
    for(int i = 0; i < n; ++i) scanf("%d", &a[i]);
    mindis = 1e100;
    for(int i = 0; i < n; ++i) {
        for(int j = i + 1; j < n; ++j) {
            double v = double(a[j] - a[i]) / (j - i);
            b[0] = a[i] - v * i;
            for(int k = 1; k < n; ++k) b[k] = b[k - 1] + v;
            double tmp = get_dis(a, b);
            if(tmp < mindis) {
                mindis = tmp;
                memcpy(ans, b, n * sizeof(double));
            }
        }
    }
    printf("%.10f\n", mindis);
    for(int i = 0; i < n; ++i)
        printf("%.10f ", ans[i]);
    puts("");
}
