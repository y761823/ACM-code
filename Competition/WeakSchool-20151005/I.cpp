#include <cstdio>
#include <iostream>
#include <algorithm>
#include <cstring>
#include <cctype>
#include <queue>
using namespace std;
typedef long long LL;
#define FOR(i, s, t) for(int i = s; i <= t; ++i)
#define foreach(it, vec) for(__typeof(vec.begin()) it = vec.begin(); it != vec.end(); ++it)

const int MAXN = 85;
const int INF = 0x3f3f3f3f;

char str[26][26][31][35];
int valid[26][26][31];
char s[MAXN], now[MAXN];

int getint(char* &p) {
    int res = 0;
    while(isdigit(*p)) res = res * 10 + *p++ - '0';
    return res;
}

void getstr(char* &p) {
    int cnt = 0;
    while(isalpha(*p)) now[cnt++] = *p++;
    now[cnt] = 0;
}

char change(char c, bool upper) {
    if(upper) return toupper(c);
    return tolower(c);
}

bool issame(char *a, char *b) {
    while(*a && *b)
        if(tolower(*a++) != tolower(*b++)) return false;
    return !*a && !*b;
}

void solve() {
    char *p = s;
    while(*p) {
        if(isalpha(*p)) {
            if(isdigit(*(p + 1))) {
                char *pre = p;
                char st = *p++;
                int cnt = getint(p);
                char ed = *p++;
                if(valid[tolower(st) - 'a'][tolower(ed) - 'a'][cnt] == 1) {
                    bool first = true;
                    for(char *q = str[tolower(st) - 'a'][tolower(ed) - 'a'][cnt]; *q; ++q) {
                        if(first) putchar(change(*q, isupper(st))), first = false;
                        else putchar(change(*q, isupper(ed)));
                    }
                } else {
                    for(char *v = pre; v != p; ++v) putchar(*v);
                }
            } else {
                char st = *p;
                getstr(p);
                char ed = *(p - 1);
                printf("%s", now);
                int cnt = strlen(now) - 2;
                if(cnt <= 0) continue;
                if(valid[tolower(st) - 'a'][tolower(ed) - 'a'][cnt] == 1) {
                    if(!issame(now, str[tolower(st) - 'a'][tolower(ed) - 'a'][cnt]))
                        valid[tolower(st) - 'a'][tolower(ed) - 'a'][cnt] = INF;
                } else if(valid[tolower(st) - 'a'][tolower(ed) - 'a'][cnt] == 0) {
                    valid[tolower(st) - 'a'][tolower(ed) - 'a'][cnt] = 1;
                    strcpy(str[tolower(st) - 'a'][tolower(ed) - 'a'][cnt], now);
                }
            }
        } else {
            putchar(*p++);
        }
    }
    puts("");
}

int main() {
    while(gets(s)) solve();
}
