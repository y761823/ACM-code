////////////////////System Comment////////////////////
////Welcome to Hangzhou Dianzi University Online Judge
////http://acm.hdu.edu.cn
//////////////////////////////////////////////////////
////Username: y761823
////Nickname: Oyk
////Run ID: 
////Submit time: 2014-11-07 10:52:59
////Compiler: GUN C++
//////////////////////////////////////////////////////
////Problem ID: 2550
////Problem Title: 
////Run result: Accept
////Run time:0MS
////Run memory:296KB
//////////////////System Comment End//////////////////
#include <cstdio>
#include <iostream>
#include <algorithm>
using namespace std;

struct Node {
    int a, b;
    bool operator < (const Node &rhs) const {
        return a < rhs.a;
    }
};

Node arr[55];
char s[66];

int main() {
    int T, n;
    scanf("%d", &T);
    while(T--) {
        scanf("%d", &n);
        for(int i = 0; i < n; ++i) scanf("%d%d", &arr[i].a, &arr[i].b);
        sort(arr, arr + n);
        for(int i = 0; i < n; ++i) {
            int cnt = 0;
            s[cnt++] = '>'; s[cnt++] = '+';
            for(int j = 2; j < arr[i].a; ++j) s[cnt++] = '-';
            s[cnt++] = '+'; s[cnt++] = '>';
            s[cnt] = 0;
            for(int j = 0; j < arr[i].b; ++j) printf("%s\n", s);
            printf("\n");
        }
    }
}