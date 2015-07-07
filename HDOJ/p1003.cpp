////////////////////System Comment////////////////////
////Welcome to Hangzhou Dianzi University Online Judge
////http://acm.hdu.edu.cn
//////////////////////////////////////////////////////
////Username: y761823
////Nickname: Oyk
////Run ID: 
////Submit time: 2012-12-06 19:22:05
////Compiler: Visual C++
//////////////////////////////////////////////////////
////Problem ID: 1003
////Problem Title: 
////Run result: Accept
////Run time:15MS
////Run memory:668KB
//////////////////System Comment End//////////////////
#include <cstdio>
using namespace std;
int a[100010];
int main()
{
    int T,t,i,n,sum=0,best,bests,bestt,nows;
    scanf("%d",&T);
    for(t=1;t<=T;++t)
    {
        if(t!=1) printf("\n");
        scanf("%d",&n);
        for(i=1;i<=n;++i) scanf("%d",&a[i]);
        best=0x80000000;sum=0;nows=1;
        for(i=1;i<=n;++i)
        {
           if(sum<0) {sum=0;nows=i;}
           sum+=a[i];
           if(sum>best)
           {
                best=sum;
                bests=nows;
                bestt=i;
           }
        }
        printf("Case %d:\n%d %d %d\n",t,best,bests,bestt);
    }
    return 0;
}
