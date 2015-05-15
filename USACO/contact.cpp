/*
ID: y7618231
LANG: C++
TASK: contact
*/
#ifdef OYK_JUDGE
#define longformat "%I64d"
#else
#define longformat "%lld"
#endif // OYK_JUDGE

#include <iostream>
#include <cstdio>
#include <vector>
#include <cstring>
#include <algorithm>
using namespace std;

const int MAXN = 200010;

char s[MAXN];
int val[MAXN], cnt[13][1 << 12];
int n, a, b, len;

void calc() {
    for(int i = 0; i < len; ++i) {
        val[i] = s[i] - '0';
        cnt[1][val[i]]++;
    }
    for(int o = 2; o <= b; ++o) {
        for(int i = len - 1; i >= o - 1; --i) {
            val[i] = (val[i - 1] << 1) + s[i] - '0';
            cnt[o][val[i]]++;
        }
    }
}

void print(int val, int len) {
    for(int i = len - 1; i >= 0; --i)
        putchar('0' + ((val >> i) & 1));
}

void solve() {
    vector<pair<int, pair<int, int> > > ans;
    for(int o = a; o <= b; ++o) {
        for(int i = 0; i < (1 << b); ++i)
            if(cnt[o][i] > 0) ans.push_back(make_pair(-cnt[o][i], make_pair(o, i)));
    }
    sort(ans.begin(), ans.end());
    int c = 0, v = 0;
    for(size_t i = 0; i < ans.size(); ++i) {
        if(c == 0 || ans[i - 1].first != ans[i].first) {
            if(c == n) break;
            if(++c != 1) puts("");
            printf("%d\n", -ans[i].first);
            v = 0;
        }
        else putchar(v % 6 == 0 ? '\n' : ' ');
        print(ans[i].second.second, ans[i].second.first);
        v++;
    }
    puts("");
}

int main () {
#ifndef OYK_JUDGE
    freopen("contact.in", "r", stdin); freopen("contact.out", "w", stdout);
#endif // OYK_JUDGE
    scanf("%d%d%d", &a, &b, &n);
    len = 0;
    while(scanf("%s", s + len) != EOF) {
        len += strlen(s + len);
    }
    calc();
    solve();
}
