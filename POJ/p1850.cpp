#include <cstdio>
#include <algorithm>
#include <cstring>
#include <iostream>
#include <map>
#include <string>
using namespace std;
#define forall(i, v) for(__typeof(v.begin()) i = v.begin(); i != v.end(); ++i)
typedef long long LL;

LL c[27][27];
char s[11];

int main() {
    for(int i = 0; i <= 26; ++i) {
        c[i][0] = 1;
        for(int j = 1; j <= 10; ++j)
            c[i][j] = c[i - 1][j] + c[i - 1][j - 1];
    }

    scanf("%s", s);
    int n = strlen(s);

    for(int i = 1; i < n; ++i)
        if(s[i - 1] >= s[i]) return puts("0"), 0;

    LL res = 0;
    for(int i = 1; i < n; ++i)
        res += c[26][i];
    for(int i = 0; i < n; ++i) {
        for(char cc = (i > 0 ? s[i - 1] + 1 : 'a'); cc < s[i]; ++cc) {
            res += c['z' - cc][n - i - 1];
        }
    }
    cout<<res + 1<<endl;
}
