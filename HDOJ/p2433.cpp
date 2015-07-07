////////////////////System Comment////////////////////
////Welcome to Hangzhou Dianzi University Online Judge
////http://acm.hdu.edu.cn
//////////////////////////////////////////////////////
////Username: y761823
////Nickname: Oyk
////Run ID: 
////Submit time: 2013-04-25 13:55:54
////Compiler: GUN C++
//////////////////////////////////////////////////////
////Problem ID: 2433
////Problem Title: 
////Run result: Accept
////Run time:953MS
////Run memory:432KB
//////////////////System Comment End//////////////////
#include<stdio.h>
#include<string.h>
#include<iostream>
using namespace std;
#define N 110
#define M 3030
#define INF 0x3fffff


struct node
{
int from,to,next;
}edge[M*2];


int n,m,ans;
int mark[M*2];
int pre[N],flag[N];
int cost[N],low[N];
int que[10*M]; 
int qf,qd;


int spfa(int s)
{
int cur,nwnode,v;
qf=1; qd=0;
for(int i=1;i<=n;i++)
{
low[i]=INF;
flag[i]=0;
}
flag[s]=1;
low[s]=0;
que[0]=s;
while(qf>qd)
{
cur=que[qd++];
flag[cur]=0;
for(int p=pre[cur];p!=-1;p=edge[p].next)
{
if(mark[p]==0)
if(low[v=edge[p].to]>low[cur]+1)
{
low[v]=low[cur]+1;
if(flag[v]==0)
{
flag[v]=1;
que[qf++]=v;
}
}
}
}
int sum=0;
for(int i=1;i<=n;i++)
sum+=low[i];
return sum;
}


int main()
{
while(scanf("%d%d",&n,&m)!=EOF)
{
ans=0;
memset(pre,-1,sizeof(pre));
memset(mark,0,sizeof(mark));
memset(cost,0,sizeof(cost));
for(int i=0;i<m;i++)
{
int x,y;
scanf("%d%d",&x,&y);


edge[2*i].from=x;
edge[2*i].to=y;
edge[2*i].next=pre[x];
pre[x]=2*i;


edge[2*i+1].from=y;
edge[2*i+1].to=x;
edge[2*i+1].next=pre[y];
pre[y]=2*i+1;
}
for(int i=1;i<=n;i++)
{
cost[i]=spfa(i);
ans+=cost[i];
}
int tmpu,tmpv,x,y;
for(int i=0;i<m;i++)
{
memset(mark,0,sizeof(mark));
mark[2*i]=1; mark[2*i+1]=1;
x=edge[2*i].from;  y=edge[2*i].to;
tmpu=spfa(x);
tmpv=spfa(y);
if(tmpu>=INF||tmpv>=INF)
printf("INF\n");
else
printf("%d\n",ans+tmpu+tmpv-cost[x]-cost[y]);
}
}
return 0;
}
