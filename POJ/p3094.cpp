#include <cstdio>
#include <algorithm>
#include <cstring>
#include <algorithm>
#include <cctype>
using namespace std;

const int MAXN = 256;

char s[MAXN];

int main() {
    while(gets(s)) {
        if(*s == '#') break;
        int n = strlen(s), res = 0;
        for(int i = 0; i < n; ++i) {
            if(isalpha(s[i])) res += (i + 1) * (s[i] - 'A' + 1);
        }
        printf("%d\n", res);
    }
}
