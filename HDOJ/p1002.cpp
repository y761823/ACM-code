////////////////////System Comment////////////////////
////Welcome to Hangzhou Dianzi University Online Judge
////http://acm.hdu.edu.cn
//////////////////////////////////////////////////////
////Username: y761823
////Nickname: Oyk
////Run ID: 
////Submit time: 2012-12-06 18:16:17
////Compiler: Visual C++
//////////////////////////////////////////////////////
////Problem ID: 1002
////Problem Title: 
////Run result: Accept
////Run time:15MS
////Run memory:348KB
//////////////////System Comment End//////////////////
#include<iostream>
#include<string>
#include<cstring>
using namespace std;
#define max(a,b) a>b?a:b;
int a[1100],b[1100];
void add(int a[],int b[])
{
    int i,l,c=0;
    l=max(a[0],b[0]);
    for(i=1;i<=l;i++)
    {
        c=a[i]+b[i]+c;
        a[i]=c%10;
        c=c/10;
    }
    if(c>0){++l;a[0]=l;a[l]=c;}
    else{a[0]=l;}
}

void turn(string s,int a[])
{
    int i,l=s.length();
    a[0]=l;
    for(i=1;i<=l;++i)
    {
        a[i]=s[l-i]-'0';
    }
}

int main()
{
    int T,t=0,i;
    string s;
    cin>>T;
    while(T--)
    {
        memset(a,0,sizeof(a));
        memset(b,0,sizeof(b));
        if(++t!=1) cout<<endl;
        cout<<"Case "<<t<<":"<<endl;;
        cin>>s;
        cout<<s<<" + ";
        turn(s,a);
        cin>>s;
        turn(s,b);
        cout<<s<<" = ";
        add(a,b);
        for(i=a[0];i>=1;--i) cout<<a[i];
        cout<<endl;
    }
    return 0;
}
