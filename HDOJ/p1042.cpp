////////////////////System Comment////////////////////
////Welcome to Hangzhou Dianzi University Online Judge
////http://acm.hdu.edu.cn
//////////////////////////////////////////////////////
////Username: y761823
////Nickname: Oyk
////Run ID: 
////Submit time: 2013-08-20 13:16:56
////Compiler: GUN C++
//////////////////////////////////////////////////////
////Problem ID: 1042
////Problem Title: 
////Run result: Accept
////Run time:3093MS
////Run memory:1680KB
//////////////////System Comment End//////////////////
//模板测试
#include <iostream>
#include <cstdio>
#include <cstring>
#include <string>
#include <algorithm>
using namespace std;

const int MAXN = 100010;

struct bign {
    int len, s[MAXN];

    bign () {
        memset(s, 0, sizeof(s));
        len = 1;
    }
    bign (int num) { *this = num; }
    bign (const char *num) { *this = num; }

    void clear() {
        memset(s, 0, sizeof(s));
        len = 1;
    }

    bign operator = (const int num) {//数字
        char s[MAXN];
        sprintf(s, "%d", num);
        *this = s;
        return *this;
    }
    bign operator = (const char *num) {//字符串
        for(int i = 0; num[i] == '0'; num++) ;  //去前导0
        if(*num == 0) --num;
        len = strlen(num);
        for(int i = 0; i < len; ++i) s[i] = num[len-i-1] - '0';
        return *this;
    }

    bign operator + (const bign &b) const {
        bign c;
        c.len = 0;
        for(int i = 0, g = 0; g || i < max(len, b.len); ++i) {
            int x = g;
            if(i < len) x += s[i];
            if(i < b.len) x += b.s[i];
            c.s[c.len++] = x % 10;
            g = x / 10;
        }
        return c;
    }

    bign operator += (const bign &b) {
        *this = *this + b;
        return *this;
    }

    void clean() {
        while(len > 1 && !s[len-1]) len--;
    }

    bign operator * (const bign &b) {
        bign c;
        c.len = len + b.len;
        for(int i = 0; i < len; ++i) {
            for(int j = 0; j < b.len; ++j) {
                c.s[i+j] += s[i] * b.s[j];
            }
        }
        for(int i = 0; i < c.len; ++i) {
            c.s[i+1] += c.s[i]/10;
            c.s[i] %= 10;
        }
        c.clean();
        return c;
    }
    bign operator *= (const bign &b) {
        *this = *this * b;
        return *this;
    }

    bign operator *= (const int &b) {//使用前要保证>len的位置都是空的
        for(int i = 0; i < len; ++i) s[i] *= b;
        for(int i = 0; i < len; ++i) {
            s[i + 1] += s[i] / 10;
            s[i] %= 10;
        }
        while(s[len]) {
            s[len + 1] += s[len] / 10;
            s[len] %= 10;
            ++len;
        }
        return *this;
    }

    bign operator - (const bign &b) {
        bign c;
        c.len = 0;
        for(int i = 0, g = 0; i < len; ++i) {
            int x = s[i] - g;
            if(i < b.len) x -= b.s[i];
            if(x >= 0) g = 0;
            else {
                g = 1;
                x += 10;
            }
            c.s[c.len++] = x;
        }
        c.clean();
        return c;
    }
    bign operator -= (const bign &b) {
        *this = *this - b;
        return *this;
    }

    bign operator / (const bign &b) {
        bign c, f = 0;
        for(int i = len - 1; i >= 0; i--) {
            f *= 10;
            f.s[0] = s[i];
            while(f >= b) {
                f -= b;
                c.s[i]++;
            }
        }
        c.len = len;
        c.clean();
        return c;
    }
    bign operator /= (const bign &b) {
        *this  = *this / b;
        return *this;
    }

    bign operator % (const bign &b) {
        bign r = *this / b;
        r = *this - r*b;
        return r;
    }
    bign operator %= (const bign &b) {
        *this = *this % b;
        return *this;
    }

    bool operator < (const bign &b) {
        if(len != b.len) return len < b.len;
        for(int i = len-1; i >= 0; i--) {
            if(s[i] != b.s[i]) return s[i] < b.s[i];
        }
        return false;
    }

    bool operator > (const bign &b) {
        if(len != b.len) return len > b.len;
        for(int i = len-1; i >= 0; i--) {
            if(s[i] != b.s[i]) return s[i] > b.s[i];
        }
        return false;
    }

    bool operator == (const bign &b) {
        return !(*this > b) && !(*this < b);
    }

    bool operator != (const bign &b) {
        return !(*this == b);
    }

    bool operator <= (const bign &b) {
        return *this < b || *this == b;
    }

    bool operator >= (const bign &b) {
        return *this > b || *this == b;
    }

    string str() const {
        string res = "";
        for(int i = 0; i < len; ++i) res = char(s[i]+'0') + res;
        return res;
    }
};

istream& operator >> (istream &in, bign &x) {
    string s;
    in >> s;
    x = s.c_str();
    return in;
}

ostream& operator << (ostream &out, const bign &x) {
    out << x.str();
    return out;
}

bign ans;

void solve(int n) {
    ans.clear();
    ans.len = ans.s[0] = 1;
    for(int i = 2; i <= n; ++i) ans *= i;
    cout<<ans<<endl;
}

int main() {
    int n;
    while(scanf("%d", &n)!=EOF) {
        //cout<<f[n]<<endl;
        solve(n);
    }
    return 0;
}
