#include <cstdio>
#include <iostream>
#include <algorithm>
#include <cstring>
#include <cctype>
#include <ext/rope>
using namespace std;
using __gnu_cxx::crope;

const int MAXN = 10010;

char op[MAXN];
crope txt, board;
int T, m, cbeg, pos, mode;

void change(char c) {
    int l = txt.length(), bl = board.length();
    if(c == 'L') {
        pos = max(0, pos - 1);
    } else if(c == 'R') {
        pos = min(l, pos + 1);
    } else if(c == 'S') {
        mode ^= 1;
        cbeg = -1;
    } else if(c == 'D') {
        if(cbeg == -1) {
            if(pos < l) txt.erase(pos, 1);
        } else {
            if(cbeg < pos) txt.erase(cbeg, pos - cbeg), pos = cbeg;
            if(pos < cbeg) txt.erase(pos, cbeg - pos);
            cbeg = -1;
        }
    } else if(c == 'B') {
        if(pos > 0 && l > 0) {
            txt.erase(pos - 1, 1);
            pos--;
        }
        cbeg = -1;
    } else if(c == 'C') {
        if(cbeg == -1) {
            cbeg = pos;
        } else {
            if(cbeg < pos) board = txt.substr(cbeg, pos - cbeg);
            if(pos < cbeg) board = txt.substr(pos, cbeg - pos);
            if(cbeg == pos) board.clear();
            cbeg = -1;
        }
    } else if(c == 'V') {
        if(mode == 0 && bl + l <= m) {
            txt = txt.substr(0, pos) + board + txt.substr(pos, l - pos);
            pos += bl;
        }
        if(mode == 1 && pos + bl < m) {
            txt.erase(pos, min(bl, l - pos));
            txt = txt.substr(0, pos) + board + txt.substr(pos, l - pos);
            pos += bl;
        }
        cbeg = -1;
    } else {
        if(mode == 0 && l < m) {
            txt = txt.substr(0, pos) + c + txt.substr(pos, l - pos);
            pos++;
        }
        if(mode == 1 && pos < m) {
            if(pos < l) txt.erase(pos, 1);
            txt = txt.substr(0, pos) + c + txt.substr(pos, l - pos);
            pos++;
        }
        cbeg = -1;
    }
    //printf("#debug %c %s\n", c, txt.c_str());
}

int main() {
    scanf("%d", &T);
    while(T--) {
        scanf("%d%s", &m, op);
        txt.clear();
        board.clear();
        cbeg = -1;
        pos = 0;
        mode = 0;
        for(int i = 0; op[i]; ++i)
            change(op[i]);
        if((int)txt.length() == 0) puts("NOTHING");
        else printf("%s\n", txt.c_str());
    }
}
