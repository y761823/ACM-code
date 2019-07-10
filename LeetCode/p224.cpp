class Solution {
public:
    int calculate(string s) {
        this->s = s;
        cur = 0;
        return expr();
    }
    
    int expr() {
        int res = factor();
        
        while (true) {
            char c = read();
            if (c != '+' && c != '-')
                break;
            cur++;
            int rhs = factor();
            if (c == '+')
                res += rhs;
            else // c == '-'
                res -= rhs;
        }
        return res;
    }
    
    int factor() {
        int res = 0;
        char c = read();
        if (c == '(') {
            cur++;
            res = expr();
            cur++;
        } else {
            while (isdigit(c = read())) {
                res = res * 10 + (c - '0');
                cur++;
            }
        }
        return res;
    }
    
private:
    char read() {
        while (cur < s.size() && s[cur] == ' ')
            cur++;
        return cur < s.size() ? s[cur] : 0;
    }
    
    string s;
    size_t cur;
};
