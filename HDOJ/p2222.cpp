////////////////////System Comment////////////////////
////Welcome to Hangzhou Dianzi University Online Judge
////http://acm.hdu.edu.cn
//////////////////////////////////////////////////////
////Username: y761823
////Nickname: Oyk
////Run ID: 
////Submit time: 2013-05-09 17:04:55
////Compiler: GUN C++
//////////////////////////////////////////////////////
////Problem ID: 2222
////Problem Title: 
////Run result: Accept
////Run time:250MS
////Run memory:28480KB
//////////////////System Comment End//////////////////
#include <cstdio>
#include <cstring>
#include <queue>

struct node{
    node *fail;
    node *next[26];
    int cnt;
    node(){
        fail = 0; cnt = 0;
        memset(next, 0, sizeof(next));
    }
};

char pattern[55], str[1000010];

void buildTire(char *s, node *root){//把s插入tire树
    node *p = root;
    int i, index;
    for(i = 0; s[i] != '\0'; ++i){
        index = s[i] - 'a';
        if(!p->next[index]) p->next[index] = new node();
        p = p->next[index];
    }
    p->cnt++;
}

void buildAutomaton(node *root){//构造失配指针
    std::queue<node*> que;
    que.push(root);
    while(!que.empty()){
        node *tmp = que.front(); que.pop();
        node *p = 0;
        for(int i = 0; i < 26; ++i){
            if(!tmp->next[i]) continue;
            if(tmp == root) tmp->next[i]->fail = root;
            else{
                p = tmp->fail;
                while(p){
                    if(p->next[i] != NULL){
                        tmp->next[i]->fail = p->next[i];
                        break;
                    }
                    p = p->fail;
                }
                if(!p) tmp->next[i]->fail = root;
            }
            que.push(tmp->next[i]);
        }
    }
}

int query(char *s, node *root){
    int ans = 0, index;
    node *p = root;
    for(int i = 0; s[i] != '\0'; ++i){
        index = str[i] - 'a';
        while(!p->next[index] && p != root) p = p->fail;
        p = p->next[index];
        if(!p) p = root;
        node *tmp = p;
        while(tmp != root && tmp->cnt != -1){
            ans += tmp->cnt;
            tmp->cnt = -1;
            tmp = tmp->fail;
        }
    }
    return ans;
}

int main(){
    int T, n;
    scanf("%d",&T);
    while(T--){
        scanf("%d",&n);
        node *root = new node();
        while(n--){
            scanf("%s",pattern);
            buildTire(pattern, root);
        }
        buildAutomaton(root);
        scanf("%s",str);
        printf("%d\n",query(str, root));
    }
    return 0;
}
