////////////////////System Comment////////////////////
////Welcome to Hangzhou Dianzi University Online Judge
////http://acm.hdu.edu.cn
//////////////////////////////////////////////////////
////Username: y761823
////Nickname: Oyk
////Run ID: 
////Submit time: 2014-11-07 10:48:52
////Compiler: GUN C++
//////////////////////////////////////////////////////
////Problem ID: 1092
////Problem Title: 
////Run result: Accept
////Run time:0MS
////Run memory:336KB
//////////////////System Comment End//////////////////
#include <iostream>
using namespace std;

int main() {
    int n, sum, a;
    while(cin>>n && n) {
        sum = 0;
        while(n--) cin>>a, sum += a;
        cout<<sum<<endl;
    }
}