class LRUCache {
    typedef list<pair<int, int>>::iterator Iter;
    list<pair<int, int>> m_list;
    unordered_map<int, Iter> m_map;
    int cap;
public:
    LRUCache(int capacity) {
        cap = capacity;
    }
    
    int get(int key) {
        auto it = m_map.find(key);
        if (it != m_map.end())
            m_list.splice(m_list.end(), m_list, it->second);
        return it != m_map.end() ? it->second->second : -1;
    }
    
    void put(int key, int value) {
        auto it = m_map.find(key);
        if (it != m_map.end()) {
            m_list.splice(m_list.end(), m_list, it->second);
            it->second->second = value;
        } else {
            if (m_map.size() == cap) {
                m_map.erase(m_list.front().first);
                m_list.pop_front();
            }
            m_list.push_back(make_pair(key, value));
            m_map.insert(make_pair(key, prev(m_list.end())));
        }
    }
};

/**
 * Your LRUCache object will be instantiated and called as such:
 * LRUCache obj = new LRUCache(capacity);
 * int param_1 = obj.get(key);
 * obj.put(key,value);
 */
