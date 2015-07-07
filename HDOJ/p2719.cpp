////////////////////System Comment////////////////////
////Welcome to Hangzhou Dianzi University Online Judge
////http://acm.hdu.edu.cn
//////////////////////////////////////////////////////
////Username: y761823
////Nickname: Oyk
////Run ID: 
////Submit time: 2014-11-07 10:56:38
////Compiler: GUN C++
//////////////////////////////////////////////////////
////Problem ID: 2719
////Problem Title: 
////Run result: Accept
////Run time:0MS
////Run memory:284KB
//////////////////System Comment End//////////////////
#include <cstdio>
#include <iostream>
#include <algorithm>
using namespace std;

char s[110];

int main() {
    while(gets(s)) {
        if(s[0] == '#') break;
        for(int i = 0; s[i]; ++i) {
            switch(s[i]) {
                case ' ':printf("%%20");break;
                case '!':printf("%%21");break;
                case '$':printf("%%24");break;
                case '%':printf("%%25");break;
                case '(':printf("%%28");break;
                case ')':printf("%%29");break;
                case '*':printf("%%2a");break;
                default:printf("%c", s[i]);break;
            }
        }
        printf("\n");
    }
}