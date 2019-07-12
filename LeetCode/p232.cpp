class MyQueue {
public:
    /** Initialize your data structure here. */
    MyQueue() {
        
    }
    
    /** Push element x to the back of queue. */
    void push(int x) {
        sin.push(x);
    }
    
    /** Removes the element from in front of queue and returns that element. */
    int pop() {
        int res = peek();
        sout.pop();
        return res;
    }
    
    /** Get the front element. */
    int peek() {
        ensureOut();
        return sout.top();
    }
    
    /** Returns whether the queue is empty. */
    bool empty() {
        return sin.empty() && sout.empty();
    }
    
private:
    void ensureOut() {
        if (sout.empty()) {
            while (!sin.empty())
                sout.push(sin.top()), sin.pop();
        }
    }
    
    std::stack<int> sin, sout;
};

/**
 * Your MyQueue object will be instantiated and called as such:
 * MyQueue* obj = new MyQueue();
 * obj->push(x);
 * int param_2 = obj->pop();
 * int param_3 = obj->peek();
 * bool param_4 = obj->empty();
 */
