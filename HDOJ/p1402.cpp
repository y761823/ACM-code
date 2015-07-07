////////////////////System Comment////////////////////
////Welcome to Hangzhou Dianzi University Online Judge
////http://acm.hdu.edu.cn
//////////////////////////////////////////////////////
////Username: y761823
////Nickname: Oyk
////Run ID: 
////Submit time: 2014-11-16 17:57:15
////Compiler: GUN C++
//////////////////////////////////////////////////////
////Problem ID: 1402
////Problem Title: 
////Run result: Accept
////Run time:140MS
////Run memory:9148KB
//////////////////System Comment End//////////////////
#include <cmath>
#include <algorithm>
#include <cstdio>
#include <iostream>
#include <cstring>
#include <complex>
using namespace std;
typedef complex<double> Complex;
const double PI = acos(-1);

void fft_prepare(int maxn, Complex *&e) {
    e = new Complex[2 * maxn - 1];
    e += maxn - 1;
    e[0] = Complex(1, 0);
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

const int MAXN = 131072;
Complex x1[MAXN], x2[MAXN];
char s1[MAXN / 2], s2[MAXN / 2];
int sum[MAXN];

int main() {
    Complex* e = 0;
    fft_prepare(MAXN, e);
    while(scanf("%s%s",s1,s2) != EOF) {
        int n1 = strlen(s1);
        int n2 = strlen(s2);
        int n = 1;
        while(n < n1 * 2 || n < n2 * 2) n <<= 1;
        for(int i = 0; i < n; ++i) {
            x1[i] = i < n1 ? s1[n1 - 1 - i] - '0' : 0;
            x2[i] = i < n2 ? s2[n2 - 1 - i] - '0' : 0;
        }

        dft(x1, n, 1, e, MAXN);
        dft(x2, n, 1, e, MAXN);
        for(int i = 0; i < n; ++i) x1[i] = x1[i] * x2[i];
        dft(x1, n, -1, e, MAXN);
        for(int i = 0; i < n; ++i) x1[i] /= n;

        for(int i = 0; i < n; ++i) sum[i] = round(x1[i].real());
        for(int i = 0; i < n; ++i) {
            sum[i + 1] += sum[i] / 10;
            sum[i] %= 10;
        }

        n = n1 + n2 - 1;
        while(sum[n] <= 0 && n > 0) --n;
        for(int i = n; i >= 0;i--) printf("%d", sum[i]);
        puts("");
    }
}
