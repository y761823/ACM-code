#include <cstdio>
#include <iostream>
#include <algorithm>
#include <cstring>
#include <cctype>
using namespace std;
typedef long long LL;
#define FOR(i, s, t) for(int i = s; i <= t; ++i)

const int MAXN = 1010;

char str[MAXN];
int T;

void remove_space() {
    char *a = str, *b = str;
    while(*b) {
        if(*b == ' ') {
            b++;
            continue;
        }
        if(*b == '\"') {
            *a++ = *b++;
            while(*b != '\"') {
                if(*b == '\\') *a++ = *b++;
                *a++ = *b++;
            }
        } else if(*b == '\'') {
            *a++ = *b++;
            while(*b != '\'') {
                if(*b == '\\') *a++ = *b++;
                *a++ = *b++;
            }
        } else if(a > str && isalnum(*(a - 1)) && isalnum(*b) && *(b - 1) == ' ') {
            *a++ = ' ';
        }
        *a++ = *b++;
    }
    *a = 0;
}

int space;
char *now;
void newline() {
    if(*now == '}') space -= 2;
    puts("");
    for(int i = 0; i < space; ++i)
        putchar(' ');
}

void print_head(char* &now) {
    bool flag = false;
    while(*now == '#') {
        flag = true;
        while(*now != '>') {
            if(*now == '<') putchar(' ');
            putchar(*now++);
        }
        putchar(*now++);
        newline();
    }
    if(flag) newline();
}

const char op[] = "+-*/=<>!";
bool isoperator(char *now) {
    return strchr(op, *now) != NULL;
}

void solve() {
    remove_space();
    now = str;
    print_head(now);

    int inBracket = 0;
    while(*now) {
        if(*now == ';') {
            putchar(*now++);
            if(inBracket) putchar(' ');
            else newline();
        } else if(*now == ',') {
            putchar(*now++);
            putchar(' ');
        } else if(*now == '{') {
            newline();
            putchar(*now++);
            space += 2;
            newline();
        } else if(*now == '}') {
            putchar(*now++);
            newline();
        } else if(*now == '(') {
            inBracket++;
            putchar(*now++);
        } else if(*now == ')') {
            inBracket--;
            putchar(*now++);
        } else if(*now == '\"') {
            putchar(*now++);
            while(*now != '\"') {
                if(*now == '\\') putchar(*now++);
                putchar(*now++);
            }
            putchar(*now++);
        } else if(*now == '\'') {
            putchar(*now++);
            while(*now != '\'') {
                if(*now == '\\') putchar(*now++);
                putchar(*now++);
            }
            putchar(*now++);
        } else if(isoperator(now)) {
            putchar(' ');
            while(isoperator(now)) putchar(*now++);
            putchar(' ');
        } else {
            putchar(*now++);
        }
    }
}

int main() {
    scanf("%d", &T);
    gets(str);
    for(int t = 1; t <= T; ++t) {
        gets(str);
        printf("Case #%d:\n", t);
        solve();
    }
}
