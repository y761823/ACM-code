////////////////////System Comment////////////////////
////Welcome to Hangzhou Dianzi University Online Judge
////http://acm.hdu.edu.cn
//////////////////////////////////////////////////////
////Username: y761823
////Nickname: Oyk
////Run ID: 
////Submit time: 2013-08-16 14:56:02
////Compiler: GUN C++
//////////////////////////////////////////////////////
////Problem ID: 2494
////Problem Title: 
////Run result: Accept
////Run time:0MS
////Run memory:300KB
//////////////////System Comment End//////////////////
#include <cstdio>
#include <algorithm>
#include <iostream>
#include <cstring>
using namespace std;

const int MAXN = 110;
const int MAXT = 3610;

struct Node {
    int t, from, to;
    void read() {
        scanf("%d%d%d", &t, &from, &to);
    }
    bool operator < (const Node &rhs) const {
        return t < rhs.t;
    }
};

Node a[MAXN];
int leave[MAXN], sum_leave;//Ҫ�ڵڼ����뿪
int into[MAXN][2], sum_into;//Ҫ�ڵڼ������,0:down,1:up
bool have_in[MAXN];//�ѽ������
int T, n, rec_t, rec_a, rec_f, step, state;

void inc_time() {
    ++rec_t;
    while(rec_a < n && a[rec_a].t <= rec_t) {//��������
        if(a[rec_a].from > a[rec_a].to) {
            ++into[a[rec_a].from][0];
        }
        else {
            ++into[a[rec_a].from][1];
        }
        ++sum_into;
        ++rec_a;
    }
}

void solve() {
    sort(a, a + n);
    step = 1;
    sum_leave = sum_into = 0;
    rec_a = 0;
    rec_t = -1; inc_time();
    memset(have_in, 0, sizeof(have_in));
    while(rec_a < n || sum_into || sum_leave) {
        switch(step) {
            case 1: { //����
                if(sum_into == 0) {
                    inc_time();
                    continue;
                }
                if(into[rec_f][1]) {
                    step = 2;//����
                    state = 1;//����
                    continue;
                }
                if(into[rec_f][0]) {
                    step = 2;//����
                    state = 0;//����
                    continue;
                }
                for(int i = rec_f + 1; i <= 50; ++i)
                    if(into[i][0] || into[i][1]) {//����������
                        step = 4;//����
                        state = 1;
                        break;
                    }
                if(step == 4) {
                    printf("%02d:%02d The elevator starts to move up from floor %d.\n", rec_t / 60, rec_t %60, rec_f);
                    continue;
                }
                for(int i = 0; i < rec_f; ++i)
                    if(into[i][0] || into[i][1]) {//����������
                        step = 5;//����
                        state = 0;
                        break;
                    }
                if(step == 5) {
                    printf("%02d:%02d The elevator starts to move down from floor %d.\n", rec_t / 60, rec_t %60, rec_f);
                    continue;
                }
                break;
            }
            case 2: {//����
                printf("%02d:%02d The elevator door is opening.\n", rec_t / 60, rec_t %60);
                inc_time();
                step = 7;//�뿪
                break;
            }
            case 3: {//����
                printf("%02d:%02d The elevator door is closing.\n", rec_t / 60, rec_t %60);
                inc_time();
                if(into[rec_f][state]) {//����Ҫ����
                    step = 2;
                    continue;
                }
                step = 8;
                break;
            }
            case 4: {//����
                ++rec_f;
                inc_time();
                if(into[rec_f][1] || leave[rec_f]) {
                    printf("%02d:%02d The elevator stops at floor %d.\n", rec_t / 60, rec_t %60, rec_f);
                    step = 2;
                    continue;
                }
                if(sum_leave) continue;
                bool flag = true;
                for(int i = rec_f + 1; i <= 50; ++i) {
                    if(into[i][1] || into[i][0]) {
                        flag = false;
                        break;
                    }
                }
                if(flag) {
                    printf("%02d:%02d The elevator stops at floor %d.\n", rec_t / 60, rec_t %60, rec_f);
                    state = 0, step = 2;
                }
                break;
            }
            case 5: {//����
                --rec_f;
                inc_time();
                if(into[rec_f][0] || leave[rec_f]) {
                    printf("%02d:%02d The elevator stops at floor %d.\n", rec_t / 60, rec_t %60, rec_f);
                    step = 2;
                    continue;
                }
                if(sum_leave) continue;
                bool flag = true;
                for(int i = 0; i < rec_f; ++i) {
                    if(into[i][1] || into[i][0]) {
                        flag = false;
                        break;
                    }
                }
                if(flag) {
                    printf("%02d:%02d The elevator stops at floor %d.\n", rec_t / 60, rec_t %60, rec_f);
                    state = 1, step = 2;
                }
                break;
            }
            case 6: {//����
                if(into[rec_f][state]) {
                    printf("%02d:%02d %d people enter the elevator.\n", rec_t / 60, rec_t %60, into[rec_f][state]);
                    sum_into -= into[rec_f][state];
                    into[rec_f][state] = 0;
                    for(int i = 0; i < rec_a; ++i)
                        if(a[i].from == rec_f && state == (a[i].from < a[i].to) && !have_in[i]) {
                            have_in[i] = true;
                            ++leave[a[i].to];
                            ++sum_leave;
                            //in_ele[i] = true;
                        }
                    inc_time();
                }
                if(!into[rec_f][state]) step = 3;//����Ҫ�����Ͳ�����
                break;
            }
            case 7: {//�뿪
                if(leave[rec_f]) {
                    printf("%02d:%02d %d people leave the elevator.\n", rec_t / 60, rec_t %60, leave[rec_f]);
                    sum_leave -= leave[rec_f];
                    leave[rec_f] = 0;
                    inc_time();
                }
                if(sum_leave == 0 && state == 1) {
                    bool flag = true;
                    for(int i = 0; i < rec_a; ++i) {
                        if(!have_in[i] && a[i].from == rec_f && a[i].to > rec_f) {
                            flag = false;
                            break;
                        }
                        if(!have_in[i] && a[i].from > rec_f) {
                            flag = false;
                            break;
                        }
                    }
                    if(flag) state = 0;
                }
                else if(sum_leave == 0 && state == 0) {
                    bool flag = true;
                    for(int i = 0; i < rec_a; ++i) {
                        if(!have_in[i] && a[i].from == rec_f && a[i].to < rec_f) {
                            flag = false;
                            break;
                        }
                        if(!have_in[i] && a[i].from < rec_f) {
                            flag = false;
                            break;
                        }
                    }
                    if(flag) state = 1;
                }
                step = 6;
                break;
            }
            case 8: {//�жϹ��ź���
                if(sum_into == 0 && sum_leave == 0) {//û��Ҫ����û���ڵ�����
                    step = 1;
                    continue;
                }
                if(sum_leave == 0) {//����û���ϣ�����û�ˣ�������
                    if(state == 1) {//�Ƿ��������
                        int i;
                        for(i = rec_f + 1; i <= 50; ++i) {
                            if(into[i][1] || into[i][0]) break;
                        }
                        if(i > 50) state = 0;
                    }
                    else {//�Ƿ��������
                        int i;
                        for(i = 1; i < rec_f; ++i) {
                            if(into[i][1] || into[i][0]) break;
                        }
                        if(i == rec_f) state = 1;
                    }
                }
                if(state) printf("%02d:%02d The elevator starts to move up from floor %d.\n", rec_t / 60, rec_t %60, rec_f);
                else printf("%02d:%02d The elevator starts to move down from floor %d.\n", rec_t / 60, rec_t %60, rec_f);
                if(state) step = 4;
                else step = 5;
                break;
            }
        }
    }
    printf("%02d:%02d The elevator door is closing.\n", rec_t / 60, rec_t %60);
}

int main() {
    scanf("%d", &T);
    for(int t = 1; t <= T; ++t) {
        scanf("%d%d", &rec_f, &n);
        for(int i = 0; i < n; ++i) a[i].read();
        printf("Case %d:\n", t);
        solve();
        puts("");
    }
}
