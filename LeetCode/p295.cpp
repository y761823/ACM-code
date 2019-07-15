class MedianFinder {
public:
    /** initialize your data structure here. */
    MedianFinder() {
        
    }
    
    void addNum(int num) {
        if (left.empty() || num < left.top()) {
            left.push(num);
            if (left.size() > right.size() + 1) {
                right.push(left.top());
                left.pop();
            }
        } else {
            right.push(num);
            if (right.size() > left.size()) {
                left.push(right.top());
                right.pop();
            }
        }
    }
    
    double findMedian() {
        if (left.size() == right.size())
            return ((double)left.top() + right.top()) / 2;
        else
            return left.top();
    }
    
private:
    priority_queue<int> left;
    priority_queue<int, std::vector<int>, std::greater<int>> right;
};

/**
 * Your MedianFinder object will be instantiated and called as such:
 * MedianFinder* obj = new MedianFinder();
 * obj->addNum(num);
 * double param_2 = obj->findMedian();
 */
