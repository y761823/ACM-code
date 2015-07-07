////////////////////System Comment////////////////////
////Welcome to Hangzhou Dianzi University Online Judge
////http://acm.hdu.edu.cn
//////////////////////////////////////////////////////
////Username: y761823
////Nickname: Oyk
////Run ID: 
////Submit time: 2013-04-29 18:08:32
////Compiler: GUN C++
//////////////////////////////////////////////////////
////Problem ID: 2255
////Problem Title: 
////Run result: Accept
////Run time:359MS
////Run memory:616KB
//////////////////System Comment End//////////////////
#include <cstdio>
#include <cctype>
#define MAXN 310
#define max(a,b) a>b?a:b
#define min(a,b) a<b?a:b
#define INF 0x7fffffff

int n;
int mat[MAXN][MAXN], slack[MAXN], Lx[MAXN], Ly[MAXN], left[MAXN];
bool S[MAXN], T[MAXN];

bool dfs(int i)
{
    S[i] = true;
    for(int j = 1; j <= n; ++j) if(!T[j]) {
        int t = Lx[i] + Ly[j] - mat[i][j];
        if(t == 0){
            T[j] = true;
            if(!left[j] || dfs(left[j])){
                left[j] = i;
                return true;
            }
        }
        else slack[j] = min(slack[j],t);
    }
    return false;
}

void update()
{
    int a = INF;
    for(int i = 1; i <= n; ++i) if(!T[i])
        a = min(slack[i],a);
    for(int i = 1; i <= n; ++i){
        if(S[i]) Lx[i] -= a;
        if(T[i]) Ly[i] += a; else slack[i] -= a;
    }
}

int KM()
{
    for(int i = 1; i <= n; ++i){
        Lx[i] = Ly[i] = left[i] = 0;
        for(int j = 1; j <= n; ++j) Lx[i] = max(Lx[i],mat[i][j]);
    }
    for(int i = 1; i <= n; ++i){
        for(int j = 1; j <= n; ++j) slack[j] = INF;
        while(1){
            for(int j = 1; j <= n; ++j) S[j] = T[j] = 0;
            if(dfs(i)) break; else update();
        }
    }
    int ans = 0;
    for(int i = 1; i <=n; ++i) ans += Lx[i] +Ly[i];
    return ans;
}

inline int readint()
{
    char c = getchar();
    while(!isdigit(c)) c = getchar();
    int x = 0;
    while(isdigit(c)){
        x = x * 10 + c - '0';
        c = getchar();
    }
    return x;
}

int main()
{
    while(scanf("%d",&n)!=EOF){
        for(int i = 1; i <= n; ++i)
            for(int j = 1; j <= n; ++j) mat[i][j] = readint();
        printf("%d\n",KM());
    }
    return 0;
}
