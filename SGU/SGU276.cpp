#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

int main() {
    int a, b;
    scanf("%d%d", &a, &b);
    b = b - a;
    if(b <= 0) printf("%d\n", 0);
    else if(b < 300) printf("%d\n", 1);
    else if(b < 15 * 60) printf("%d\n", 2);
    else if(b < 30 * 60) printf("%d\n", 3);
    else printf("%d\n", 4);
}
