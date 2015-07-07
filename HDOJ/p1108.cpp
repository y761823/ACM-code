////////////////////System Comment////////////////////
////Welcome to Hangzhou Dianzi University Online Judge
////http://acm.hdu.edu.cn
//////////////////////////////////////////////////////
////Username: y761823
////Nickname: Oyk
////Run ID: 
////Submit time: 2014-11-07 10:59:15
////Compiler: GUN C++
//////////////////////////////////////////////////////
////Problem ID: 1108
////Problem Title: 
////Run result: Accept
////Run time:0MS
////Run memory:336KB
//////////////////System Comment End//////////////////
#include <iostream>
#include <cstdio>
#include <cmath>
using namespace std;

int lcm(int a, int b) {
    return a / __gcd(a, b) * b;
}

int main() {
    int a, b;
    while(cin>>a>>b)
        cout<<lcm(a, b)<<endl;
}