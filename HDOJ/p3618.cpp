////////////////////System Comment////////////////////
////Welcome to Hangzhou Dianzi University Online Judge
////http://acm.hdu.edu.cn
//////////////////////////////////////////////////////
////Username: y761823
////Nickname: Oyk
////Run ID: 
////Submit time: 2013-04-24 17:10:43
////Compiler: GUN C++
//////////////////////////////////////////////////////
////Problem ID: 3618
////Problem Title: 
////Run result: Accept
////Run time:15MS
////Run memory:308KB
//////////////////System Comment End//////////////////
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<queue>
#define INF 0x7fffffff
using namespace std;
const int MAXN=500,MAXM=4000;
struct mcflow{
       int N,M,S,T;
       int head[MAXN],next[MAXM],to[MAXM],cost[MAXM],f[MAXM],ecnt;
       int pre[MAXN],d[MAXN];
       bool vis[MAXN];
       #define CL(x) memset(x, 0, sizeof(x));
       void init(){
            CL(head); CL(next); CL(to); CL(cost);
            ecnt = 2;
            T = S = N = M = 0;
       }
       void make_edge(int a, int b, int cc, int d){
            next[ecnt] = head[a];
            head[a] = ecnt;
            to[ecnt] = b;
            f[ecnt] = cc;
            cost[ecnt++] = d;
       }
       void insert(int a, int b, int cc, int d){
            make_edge(a, b, cc, d);
            make_edge(b, a, 0, -d);
       }
       bool spfa(){
            CL(vis);
            for(int i = 0; i <= T; ++i)
                d[i] = INF;
            queue<int> Q;
            Q.push(S);
            vis[S]=1;
            d[S] = 0;
            while(!Q.empty()){
                int u = Q.front(); Q.pop();
                vis[u] = 0;
                for(int p = head[u]; p; p = next[p]){
                    if(f[p] > 0 && d[to[p]] > d[u] + cost[p]){
                        d[to[p]] = d[u] + cost[p];
                        pre[to[p]] = p;
                        if(!vis[to[p]]){
                            vis[to[p]]=1;
                            Q.push(to[p]);
                        }
                    }
                }
            }
            return d[T] < INF;
       }
       void min_cost_flow(int &Flow, int &fee){
            Flow = fee = 0;
            while(spfa()){
                fee += d[T];
                int u = T, tmp = INF;
                while(u != S){
                    tmp=min(f[pre[u]], tmp);
                    u=to[pre[u]^1];
                }
                u=T;
                while(u != S){
                    f[pre[u]] -= tmp;
                    f[pre[u]^1] += tmp;
                    u = to[pre[u]^1];
                }
                Flow += tmp;
            }
       }
       int mincost(){
           int ret, tmp;
           min_cost_flow(tmp, ret);
           return ret;
       }
       int maxflow(){
           int ret, tmp;
           min_cost_flow(ret, tmp);
           return ret;
       }
}G;

int main()
{
    int T,m,s,t,v,i;
    scanf("%d",&T);
    while(T--){
        G.init();
        scanf("%d",&m);
        while(m--){
            scanf("%d%d%d",&s,&t,&v);
            G.insert(s,t+1,1,-v);
        }
        G.S = 401; G.T = 402;
        G.insert(G.S,0,2,0); G.insert(400,G.T,2,0);
        for(i = 0; i < 400; ++i) G.insert(i,i+1,2,0);
        printf("%d\n",-G.mincost());
    }
    return 0;
}
