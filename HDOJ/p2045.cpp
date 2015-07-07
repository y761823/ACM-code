////////////////////System Comment////////////////////
////Welcome to Hangzhou Dianzi University Online Judge
////http://acm.hdu.edu.cn
//////////////////////////////////////////////////////
////Username: y761823
////Nickname: Oyk
////Run ID: 
////Submit time: 2012-12-09 23:01:32
////Compiler: Visual C++
//////////////////////////////////////////////////////
////Problem ID: 2045
////Problem Title: 
////Run result: Accept
////Run time:15MS
////Run memory:336KB
//////////////////System Comment End//////////////////
#include <iostream>
#include <math.h>
using namespace std;
__int64 c(int x)
{
    if(x==1)
    return 1;
    if(x==2)
    return 2;
    __int64 s;
    s=pow((double)2,x-1)-c(x-1);
    return s;
}
int main()
{
    int n;
    while(cin>>n)
    {
        cout<<3*c(n)<<endl;
    }
    return 0;
}