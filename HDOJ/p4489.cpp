////////////////////System Comment////////////////////
////Welcome to Hangzhou Dianzi University Online Judge
////http://acm.hdu.edu.cn
//////////////////////////////////////////////////////
////Username: y761823
////Nickname: Oyk
////Run ID: 
////Submit time: 2013-01-23 11:28:14
////Compiler: Visual C++
//////////////////////////////////////////////////////
////Problem ID: 4489
////Problem Title: 
////Run result: Accept
////Run time:0MS
////Run memory:292KB
//////////////////System Comment End//////////////////
#include <iostream>
#include <cstring>
#define maxn 20
using namespace std;
int cv[maxn+2][maxn+2],P,D,n;
long long ans[maxn+2];
int c(int n,int m)
{
    if(n==0) return 1;
    if(n==m) return 1;
    if(cv[n][m]!=0) return cv[n][m];
    cv[n][m]=c(n-1,m-1)+c(n,m-1);
    return cv[n][m];
}
void ready()
{
    int i,j;
    ans[0]=ans[1]=1;
    for(i=2;i<=maxn;++i)
    {
        ans[i]=0;
        for(j=1;j<=i;++j)
        {
            ans[i]=ans[i]+c(j-1,i-1)*ans[j-1]*ans[i-j];
        }
        ans[i]=ans[i]>>1;
    }
    for(i=2;i<=maxn;++i) ans[i]<<=1;
}
int main()
{
    memset(cv,0,sizeof(cv));
    ready();
    cin>>P;
    while(P--)
    {
        cin>>D>>n;
        cout<<D<<' '<<ans[n]<<endl;
    }
    return 0;
}