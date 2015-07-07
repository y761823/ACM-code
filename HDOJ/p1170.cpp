////////////////////System Comment////////////////////
////Welcome to Hangzhou Dianzi University Online Judge
////http://acm.hdu.edu.cn
//////////////////////////////////////////////////////
////Username: y761823
////Nickname: Oyk
////Run ID: 
////Submit time: 2014-11-07 10:54:43
////Compiler: GUN C++
//////////////////////////////////////////////////////
////Problem ID: 1170
////Problem Title: 
////Run result: Accept
////Run time:0MS
////Run memory:296KB
//////////////////System Comment End//////////////////
#include <cstdio>
#include <iostream>
#include <algorithm>
using namespace std;

int main() {
    int T, a, b;
    char c;
    scanf("%d", &T);
    while(T--) {
        scanf(" %c%d%d", &c, &a, &b);
        switch(c) {
            case '+':printf("%d\n", a + b);break;
            case '-':printf("%d\n", a - b);break;
            case '*':printf("%d\n", a * b);break;
            case '/':
                if(a % b) printf("%.2f\n", double(a) / b);
                else printf("%d\n", a / b);
                break;
        }
    }
}