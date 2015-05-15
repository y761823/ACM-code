#include <bits/stdc++.h>
using namespace std;
typedef long long LL;

const int MAXV = 4010;

char str[MAXV];
bool palindromic[MAXV][MAXV], calc[MAXV][MAXV];
int sa[MAXV];
int n, m;

bool isPalindromic(int l, int r) {
    if(l >= r) return true;
    if(calc[l][r]) return palindromic[l][r];
    return calc[l][r] = true, palindromic[l][r] = (str[l] == str[r] && isPalindromic(l + 1, r - 1));
}

bool cmp(int a, int b) {
    int k = 0;
    while(str[a + k] == str[b + k]) k++;
    return str[a + k] < str[b + k];
}

int main() {
    scanf("%s", str);
    n = strlen(str);
    str[n] = '#';
    scanf("%s", str + n + 1);
    m = strlen(str);

    for(int i = 0; i < m; ++i) sa[i] = i;
    sort(sa, sa + m, cmp);

    int st = 0, len = 0;
    for(int c = 0; c < m - 1; ++c) {
        int a = sa[c], b = sa[c + 1];
        if((a < n) != (b < n)) {
            int k = 0;
            while(str[a + k] == str[b + k]) {
                k++;
                if(k > len && isPalindromic(a, a + k - 1))
                    st = a, len = k;
            }
        }
    }

    str[st + len] = 0;
    printf("%s\n", str + st);
}
