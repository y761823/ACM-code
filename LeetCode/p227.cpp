class Solution {
public:
    int calculate(string s) {
        this->s = s;
        cur = 0;
        return expr();
    }
    
private:
    
    int factor() {
        int res = 0;
        char c;
        while (isdigit(c = next())) {
            cur++;
            res = res * 10 + (c - '0');
        }
        return res;
    }
    
    int term() {
        int x = factor();
        char c = next();
        while (c == '*' || c == '/') {
            cur++;
            int y = factor();
            if (c == '*')
                x *= y;
            else
                x /= y;
            c = next();
        }
        return x;
    }
    
    int expr() {
        int x = term();
        char c = next();
        while (c == '+' || c == '-') {
            cur++;
            int y = term();
            if (c == '+')
                x += y;
            else
                x -= y;
            c = next();
        }
        return x;
    }
    
    char next() {
        while (cur < s.size() && s[cur] == ' ')
            cur++;
        return cur < s.size() ? s[cur] : 0;
    }
    
    string s;
    size_t cur;
};
