/**
 * // This is the interface that allows for creating nested lists.
 * // You should not implement it, or speculate about its implementation
 * class NestedInteger {
 *   public:
 *     // Return true if this NestedInteger holds a single integer, rather than a nested list.
 *     bool isInteger() const;
 *
 *     // Return the single integer that this NestedInteger holds, if it holds a single integer
 *     // The result is undefined if this NestedInteger holds a nested list
 *     int getInteger() const;
 *
 *     // Return the nested list that this NestedInteger holds, if it holds a nested list
 *     // The result is undefined if this NestedInteger holds a single integer
 *     const vector<NestedInteger> &getList() const;
 * };
 */
class NestedIterator {
public:
    NestedIterator() {
    }
    
    NestedIterator(vector<NestedInteger> &nestedList) {
        cur = nestedList.begin();
        end = nestedList.end();
        resetIt();
    }
    
    int next() {
        ensureNext();
        int res;
        if (cur->isInteger()) {
            res = cur->getInteger();
            ++cur;
            resetIt();
        } else {
            res = it->next();
        }
        return res;
    }

    bool hasNext() {
        ensureNext();
        return cur != end;
    }
    
private:
    void ensureNext() {
        while (cur != end && !cur->isInteger() && !it->hasNext()) {
            ++cur;
            resetIt();
        }
    }
    
    void resetIt() {
        if (cur != end && !cur->isInteger()) {
            it.reset(new NestedIterator(cur->getList()));
        }
    }
    
    unique_ptr<NestedIterator> it;
    vector<NestedInteger>::iterator cur, end;
};

/**
 * Your NestedIterator object will be instantiated and called as such:
 * NestedIterator i(nestedList);
 * while (i.hasNext()) cout << i.next();
 */
