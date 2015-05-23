#include <cstdio>
using namespace std;

int n, m;

int main() {
    while(scanf("%d%d", &n, &m) != EOF)
        printf("%d\n", (m - 1) % n);
}
