////////////////////System Comment////////////////////
////Welcome to Hangzhou Dianzi University Online Judge
////http://acm.hdu.edu.cn
//////////////////////////////////////////////////////
////Username: y761823
////Nickname: Oyk
////Run ID: 
////Submit time: 2012-12-08 16:25:05
////Compiler: Visual C++
//////////////////////////////////////////////////////
////Problem ID: 3068
////Problem Title: 
////Run result: Accept
////Run time:281MS
////Run memory:1364KB
//////////////////System Comment End//////////////////
#include <iostream>
#include <cstring>
#include <string>
#include <cstdio>
using namespace std;
#define MAX 110010
#define min(a,b) a<b?a:b
char sr[MAX],s[MAX<<1];
int p[MAX<<1];

void turn()
{
    s[0]='!';s[1]='#';
    int i;
    for(i=1;sr[i]!='\0';++i)
    {
        s[i<<1]=sr[i];
        s[(i<<1)+1]='#';
    }
    s[i<<1]='\0';
}
void manacher()
{
    int i,id=0,MaxId=0,ans=0;
    for(i=1;s[i]!='\0';++i)
    {
        if(i<MaxId) p[i]=min(p[id*2-i],MaxId-i);
        else p[i]=1;
        while(s[i+p[i]]==s[i-p[i]]) ++p[i];
        if(i+p[i]>MaxId)
        {
            MaxId=i+p[i];
            id=i;
        }
        if(p[i]>ans) ans=p[i];
    }
    printf("%d\n",ans-1);
}
int main()
{
    while(scanf("%s",&sr[1])!=EOF)
    {
        turn();
        manacher();
    }
    return 0;
}
