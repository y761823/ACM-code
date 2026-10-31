class LFUCache {
    struct KV {
        int key;
        int value;
    };
    std::unordered_map<int, std::list<KV>> frequency;

    struct Location {
        int freq;
        std::list<KV>::iterator it;
    };
    std::unordered_map<int, Location> locate;
    int cap = 0;
    int minf = 0;

public:
    LFUCache(int capacity) {
        cap = capacity;
    }
    
    int get(int key) {
        auto it = locate.find(key);
        if (it == locate.end()) {
            return -1;
        }
        
        inc_frequency(it);
        return it->second.it->value;
    }
    
    void put(int key, int value) {
        auto it = locate.find(key);
        if (it == locate.end()) {
            if (locate.size() == cap) {
                auto &li = frequency[minf];
                locate.erase(li.front().key);
                li.pop_front();
                if (li.empty()) {
                    frequency.erase(minf);
                }
            }

            auto &li = frequency[1];
            li.emplace_back(key, value);
            locate.emplace(key, Location{1, --li.end()});
            minf = 1;
            return;
        }
        
        inc_frequency(it);
        it->second.it->value = value;
    }

private:
    void inc_frequency(std::unordered_map<int, Location>::iterator input_it) {
        auto &cur_list = frequency[input_it->second.freq];
        auto &target_list = frequency[input_it->second.freq + 1];
        target_list.splice(target_list.end(), cur_list, input_it->second.it);
        if (cur_list.empty()) {
            frequency.erase(input_it->second.freq);
            if (input_it->second.freq == minf) {
                minf++;
            }
        }
        input_it->second.freq++;
    }
};
