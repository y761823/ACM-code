#include <cstdio>
#include <iostream>
#include <algorithm>
#include <cstring>
#include <cmath>
using namespace std;

int main() {
    int p, e, i, d, t = 0;
    while(scanf("%d%d%d%d", &p, &e, &i, &d) != EOF) {
        if(p == -1) break;
        printf("Case %d: the next triple peak occurs in %d days.\n", ++t, (5544*p+14421*e+1288*i-d+21251)%21252+1);
    }
}
