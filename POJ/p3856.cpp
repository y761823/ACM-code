#include <cstdio>
#include <iostream>
#include <cstring>
#include <algorithm>
using namespace std;

const int MAXN = 1000000;

struct Node {
    char name[55];
    int next, pre, siz;
    bool isFile, del;
};

Node a[MAXN];
int head[MAXN], ecnt, root, now;
char s[110], tmp[110];

void clear() {
    root = now = 1;
    head[root] = 0;
    ecnt = 2;
}

int new_sub(int cur, char *name, int size, bool isFile) {
    a[ecnt].pre = cur;
    strcpy(a[ecnt].name, name);
    a[ecnt].siz = size;
    a[ecnt].isFile = isFile;
    a[ecnt].next = head[cur];
    a[ecnt].del = 0;
    head[ecnt] = 0;
    return head[cur] = ecnt++;
}

int to_sub(int cur, char *name, int siz = 0, int isFile = 0) {
    for(int p = head[cur]; p; p = a[p].next)
        if(strcmp(a[p].name, name) == 0) return p;
    return new_sub(cur, name, siz, isFile);
}

int get_pre(int cur) {
    return a[cur].pre;
}

int get_root() {
    return root;
}

void _strcpy(char *&src, char *tar) {
    int len = 0;
    while(*src != '\\' && *src != 0) tar[len++] = *src, ++src;
    tar[len] = 0;
    if(*src == '\\') ++src;
}

void cd(char *s) {
    if(*s == '\\') now = get_root(), ++s;
    while(*s != 0) {
        _strcpy(s, tmp);
        now = to_sub(now, tmp);
    }
}

int str_to_num(char *s) {
    int ret = 0;
    for(int i = 0; s[i]; ++i)
        ret = ret * 10 + s[i] - '0';
    return ret;
}

void dir() {
    while(gets(s) && *s != '>') {
        int i = 0;
        for(i = 0; s[i]; ++i)
            if(s[i] == ' ') break;
        if(s[i] != ' ') {
            to_sub(now, s);
        }
        else {
            s[i] = 0;
            to_sub(now, s, str_to_num(s + i + 1), 1);
        }
    }
}

int dfs_del(int cur) {
    if(a[cur].del) return 0;
    a[cur].del = true;
    int ret = 0;
    for(int p = head[cur]; p; p = a[p].next) {
        if(a[p].isFile) ret += a[p].siz;
        else ret += dfs_del(p);
    }
    return ret;
}

void deltree(char *s) {
    if(*s == '\\') now = root, ++s;
    int cur = now;
    while(*s != 0) {
        _strcpy(s, tmp);
        cur = to_sub(cur, tmp);
    }
    printf("%d\n", dfs_del(cur));
}

int main() {
    clear();
    gets(s);
    while(strcmp(s, ">exit") != 0) {
        if(s[0] == 0) {//next exploration
            clear();
            gets(s);
        }
        if(strcmp(s, ">cd ..") == 0) {
            now = get_pre(now);
            gets(s);
            continue;
        }
        if(strncmp(s, ">cd", 3) == 0) {
            char *name = s + 4;
            while(*name == ' ') ++name;
            cd(name);
            gets(s);
            continue;
        }
        if(strcmp(s, ">dir") == 0) {
            dir();
            continue;
        }
        if(strncmp(s, ">deltree", 8) == 0) {
            char *name = s + 8;
            while(*name == ' ') ++name;
            deltree(name);
            gets(s);
            continue;
        }
    }
}
