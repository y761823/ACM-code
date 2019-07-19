class MinStack {
public:
    /** initialize your data structure here. */
    MinStack() {
        
    }
    
    void push(int x) {
        if (mint.empty() || x < getMin())
            mint.push_back(stk.size());
        stk.push_back(x);
    }
    
    void pop() {
        stk.pop_back();
        if (mint.back() >= stk.size())
            mint.pop_back();
    }
    
    int top() {
        return stk.back();
    }
    
    int getMin() {
        return stk[mint.back()];
    }
    
private:
    vector<int> stk, mint;
};

/**
 * Your MinStack object will be instantiated and called as such:
 * MinStack* obj = new MinStack();
 * obj->push(x);
 * obj->pop();
 * int param_3 = obj->top();
 * int param_4 = obj->getMin();
 */
