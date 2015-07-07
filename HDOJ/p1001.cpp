////////////////////System Comment////////////////////
////Welcome to Hangzhou Dianzi University Online Judge
////http://acm.hdu.edu.cn
//////////////////////////////////////////////////////
////Username: y761823
////Nickname: Oyk
////Run ID: 
////Submit time: 2012-11-21 12:40:16
////Compiler: Visual C++
//////////////////////////////////////////////////////
////Problem ID: 1001
////Problem Title: 
////Run result: Accept
////Run time:15MS
////Run memory:348KB
//////////////////System Comment End//////////////////
#include<iostream>
using namespace std;
int main()
{
    int n,ans,i;
    while(cin>>n)
    {
        ans=0;
        for(i=1;i<=n;i++) ans+=i;
        cout<<ans<<endl<<endl;
    }
}