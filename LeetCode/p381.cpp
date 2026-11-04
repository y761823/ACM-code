class RandomizedCollection {
public:
    RandomizedCollection() {
        
    }
    
    bool insert(int val) {
        auto &st = pos_map[val];
        st.emplace(vec.size());
        vec.emplace_back(val);
        return st.size() == 1;
    }
    
    bool remove(int val) {
        auto it = pos_map.find(val);
        if (it == pos_map.end()) {
            return false;
        }
        size_t p = *it->second.begin();
        if (p != vec.size() - 1) {
            if (vec[p] != vec.back()) {
                vec[p] = vec.back();
                pos_map[vec[p]].emplace(p);
                pos_map[vec[p]].erase(vec.size() - 1);
            } else {
                p = vec.size() - 1;
            }
        }
        it->second.erase(p);
        if (it->second.empty()) {
            pos_map.erase(it);
        }
        vec.pop_back();
        return true;
    }
    
    int getRandom() {
        return vec[rand() % vec.size()];
    }

private:
    std::vector<int> vec;
    std::unordered_map<int, std::unordered_set<int>> pos_map;
};
