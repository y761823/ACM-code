class Solution {
public:
    bool isValidSerialization(string preorder) {
        vector<int> stk{0};
        int pos = 0, n = preorder.size();
        while (pos < n && !stk.empty()) {
            if (preorder[pos] == '#') {
                stk.back()++;
                while (!stk.empty() && stk.back() == 2)
                    stk.pop_back();
            } else {
                stk.back()++;
                stk.push_back(0);
            }
            
            while (pos < n && preorder[pos] != ',')
                pos++;
            pos++;
        }
        return stk.size() == 1 && stk.front() == 1; 
    }
};
