#include <cstdio>
#include <algorithm>
#include <cstring>
#include <iostream>
using namespace std;

int n, m;

int main() {
    scanf("%d%d", &m, &n);
    if(m == 1) printf("%d\n", 1);
    else printf("%d\n", n - 1 >= m - n ? n - 1 : n + 1);
}
