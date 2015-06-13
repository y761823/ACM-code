#include <cstdio>
#include <algorithm>
#include <cstring>
#include <algorithm>
#include <cmath>
using namespace std;

const int MAXN = 1010;
const double EPS = 1e-10;

int main() {
    double n, p;
    while(scanf("%lf%lf", &n, &p) != EOF)
        printf("%.0f\n", pow(p, 1.0 / n));
}
