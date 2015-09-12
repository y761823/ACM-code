#include <cstdio>
#include <algorithm>
#include <iostream>
#include <cstring>
#include <cctype>
#include <bitset>
#include <complex>
using namespace std;
typedef long long LL;
typedef complex<double> Complex;

const double PI = acos(-1);
const int MAXN = 524288;

Complex x1[MAXN];
int sum[MAXN];
int a[MAXN / 2];
bool exist[MAXN];
int n, m;

int readint() {
    char c = getchar();
    while(!isdigit(c)) c = getchar();
    int res = 0;
    while(isdigit(c)) res = res * 10 + c - '0', c = getchar();
    return res;
}

void fft_prepare(int maxn, Complex *&e) {
    e = new Complex[2 * maxn - 1];
    e += maxn - 1;
    e[0] = 1;
    for (int i = 1; i < maxn; i <<= 1)
        e[i] = Complex(cos(2 * PI * i / maxn), sin(2 * PI * i / maxn));
    for (int i = 3; i < maxn; i++)
        if ((i & -i) != i) e[i] = e[i - (i & -i)] * e[i & -i];
    for (int i = 1; i < maxn; i++) e[-i] = e[maxn - i];
}
/* f = 1: dft; f = -1: idft */
void dft(Complex *a, int N, int f, Complex *e, int maxn) {
    int d = maxn / N * f;
    Complex x;
    for (int n = N, m; m = n / 2, m >= 1; n = m, d *= 2)
        for (int i = 0; i < m; i++)
            for (int j = i; j < N; j += n)
                x = a[j] - a[j + m], a[j] += a[j + m], a[j + m] = x * e[d * i];
    for (int i = 0, j = 1; j < N - 1; j++) {
        for (int k = N / 2; k > (i ^= k); k /= 2);
        if (j < i) swap(a[i], a[j]);
    }
}

void calc(Complex e[], int n) {
    int nn = 1;
    while(nn < n * 2) nn <<= 1;
    for(int i = 0; i < nn; ++i) {
        x1[i] = i < n ? exist[i] : 0;
    }
    dft(x1, nn, 1, e, MAXN);
    for(int i = 0; i < nn; ++i) x1[i] = x1[i] * x1[i];
    dft(x1, nn, -1, e, MAXN);
    for(int i = 0; i < nn; ++i) x1[i] /= nn;

    for(int i = 0; i < nn; ++i) sum[i] = round(x1[i].real());
    for(int i = 0; i < n; ++i) sum[i] |= exist[i];
}

int main() {
    Complex* e = 0;
    fft_prepare(MAXN, e);
    while(scanf("%d", &n) != EOF) {
        memset(exist, 0, sizeof(exist));
        memset(sum, 0, sizeof(sum));
        for(int i = 0; i < n; ++i) {
            a[i] = readint();
            exist[a[i]] = true;
        }
        calc(e, *max_element(a, a + n) + 1);

        m = readint();
        int res = 0;
        for(int i = 0; i < m; ++i)
            res += (sum[readint()] > 0);
        printf("%d\n", res);
    }
}
