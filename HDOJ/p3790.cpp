////////////////////System Comment////////////////////
////Welcome to Hangzhou Dianzi University Online Judge
////http://acm.hdu.edu.cn
//////////////////////////////////////////////////////
////Username: y761823
////Nickname: Oyk
////Run ID: 
////Submit time: 2012-12-08 00:23:50
////Compiler: Visual C++
//////////////////////////////////////////////////////
////Problem ID: 3790
////Problem Title: 
////Run result: Accept
////Run time:187MS
////Run memory:976KB
//////////////////System Comment End//////////////////
#include <iostream>
#include <cstdio>
#include <cstring>
#include <vector>
#include <queue>
#include <cstddef>
#define MAX 0x7fffffff
using std::vector;
using std::queue;
struct edge{
    int to,w,c;
}temp;
vector<edge> map[1010];
int n,m,s,t;
int key[1010],cost[1010];
bool exist[1010];

void spfa()
{
    int now;
    size_t i,size;
    for(int i=1;i<=n;++i)
        key[i]=cost[i]=MAX;
    memset(exist,true,sizeof(exist));
    queue<int> q;
    q.push(s);key[s]=0;cost[s]=0;exist[s]=false;
    while(!q.empty())
    {
        now=q.front();q.pop();size=map[now].size();exist[now]=true;
        for(i=0;i<size;++i)
            if(key[map[now][i].to]>key[now]+map[now][i].w ||
              (key[map[now][i].to]==key[now]+map[now][i].w && cost[map[now][i].to]>cost[now]+map[now][i].c))
            {
                key[map[now][i].to]=key[now]+map[now][i].w;
                cost[map[now][i].to]=cost[now]+map[now][i].c;
                if(exist[map[now][i].to])
                {
                    q.push(map[now][i].to);
                    exist[map[now][i].to]=false;
                }
            }
    }
    printf("%d %d\n",key[t],cost[t]);
}

int main()
{
    int i,a,b,d,p;
    while(scanf("%d%d",&n,&m) && n)
    {
        for(i=1;i<=n;++i) map[i].clear();
        while(m--)
        {
            scanf("%d%d%d%d",&a,&b,&d,&p);
            temp.to=b;temp.w=d;temp.c=p;
            map[a].push_back(temp);
            temp.to=a;
            map[b].push_back(temp);
        }
        scanf("%d%d",&s,&t);
        spfa();
    }
    return 0;
}
