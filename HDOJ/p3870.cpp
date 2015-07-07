////////////////////System Comment////////////////////
////Welcome to Hangzhou Dianzi University Online Judge
////http://acm.hdu.edu.cn
//////////////////////////////////////////////////////
////Username: y761823
////Nickname: Oyk
////Run ID: 
////Submit time: 2013-06-02 16:44:12
////Compiler: GUN C++
//////////////////////////////////////////////////////
////Problem ID: 3870
////Problem Title: 
////Run result: Accept
////Run time:421MS
////Run memory:9180KB
//////////////////System Comment End//////////////////
#include <cstdio>
#include <queue>
#include <cstring>
#define INF 0x3fffffff
#define MAXN 200000
#define MAXM 1500010
#define LL long long
using namespace std;

int d[MAXN] ,head[MAXN], to[MAXM], next[MAXM], cost[MAXM], ecnt;
bool vis[MAXN];

inline void addEdge(int u, int v, int w)
{
    next[ecnt] = head[u]; head[u] = ecnt;
    to[ecnt] = v; cost[ecnt++] = w;
}

void spfa(int S, int T){
    for(int i = 0; i <= T; ++i) d[i] = INF;
    deque<int> Q; LL cntque = 1, sumque = 0;
    Q.push_back(S);
    vis[S]=1;
    d[S] = 0;
    while(!Q.empty()){
        int u = Q.front(); Q.pop_front();
        if(d[u] * cntque > sumque) {Q.push_back(u); continue;}//LLL optimization
        sumque -= d[u]; cntque--;
        vis[u] = 0;
        for(int p = head[u]; p; p = next[p]){
            if(d[to[p]] > d[u] + cost[p]){
                d[to[p]] = d[u] + cost[p];
                if(d[to[p]] < d[Q.front()]){//SLF optimization
                    Q.push_front(to[p]);
                    sumque += d[to[p]]; cntque++;
                } else
                    if(!vis[to[p]]){
                        vis[to[p]]=1;
                        Q.push_back(to[p]);
                        sumque += d[to[p]]; cntque++;
                    }
            }
        }
    }
    printf("%d\n",d[T]);
}

int getInt(){
    char ch = getchar();
    while(ch<'0'||ch>'9')ch = getchar();
    int num = 0;
    while(ch >= '0' && ch <= '9'){
        num = num*10 + ch - '0';
        ch = getchar();
    }
    return num;
}

int main()
{
    int T, i, j, x, n, ss, tt;
    scanf("%d",&T);
    while(T--){
        scanf("%d",&n);
        ss = (n-1)*(n-1); tt = ss +1;
        memset(head, 0, (tt+1)*sizeof(int));
        ecnt = 1;
        for(i = 0; i < n; ++i)
            for(j = 0; j < n; ++j){
                x = getInt();//scanf("%d",&x);
                if(j != n-1){
                    if(i == 0) addEdge(ss,i*(n-1)+j,x);
                    else if(i == n-1) addEdge((i-1)*(n-1)+j,tt,x);
                    else {addEdge(i*(n-1)+j,(i-1)*(n-1)+j,x);addEdge((i-1)*(n-1)+j,i*(n-1)+j,x);}
                }
                if(i != n-1){
                    if(j == 0) addEdge(i*(n-1)+j,tt,x);
                    else if(j == n-1) addEdge(ss,i*(n-1)+j-1,x);
                    else {addEdge(i*(n-1)+j,i*(n-1)+j-1,x);addEdge(i*(n-1)+j-1,i*(n-1)+j,x);}
                }
            }
        spfa(ss, tt);
    }
    return 0;
}
