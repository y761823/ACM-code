class RandomizedSet {
public:
    RandomizedSet() {

    }
    
    bool insert(int val) {
        if (maps.count(val)) {
            return false;
        }
        maps.emplace(val, values.size());
        values.push_back(val);
        return true;
    }
    
    bool remove(int val) {
        auto it = maps.find(val);
        if (it == maps.end()) {
            return false;
        }
        size_t pos = it->second;
        if (pos != maps.size() - 1) {
            maps[values.back()] = pos;
            values[pos] = values.back();
        }
        maps.erase(it);
        values.pop_back();
        return true;
    }
    
    int getRandom() {
        size_t idx = rand() % values.size();
        return values[idx];
    }

private:
    std::vector<int> values;
    std::unordered_map<int, size_t> maps;
};
