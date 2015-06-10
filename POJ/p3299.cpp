#include <cstdio>
#include <algorithm>
#include <cstring>
#include <algorithm>
#include <cmath>
using namespace std;

char c1, c2;
double t, d, h, a, b;

void get(char c, double x) {
    if(c == 'T') t = x;
    if(c == 'D') d = x;
    if(c == 'H') h = x;
}

int main() {
    while(scanf(" %c%lf %c%lf", &c1, &a, &c2, &b) != EOF && c1 != 'E') {
        t = d = h = 1e10;
        get(c1, a); get(c2, b);
        if(t == 1e10) t = h - (0.5555) * (6.11 * exp(5417.7530 * ((1/273.16) - (1/(d+273.16)))) - 10.0);
        if(d == 1e10) d = 1 / (1/273.16 - log((((h - t) / 0.5555) + 10) / 6.11) / 5417.7530) - 273.16;
        if(h == 1e10) h = t + (0.5555) * (6.11 * exp(5417.7530 * ((1/273.16) - (1/(d+273.16)))) - 10.0);
        printf("T %.1f D %.1f H %.1f\n", t, d, h);
    }
}
