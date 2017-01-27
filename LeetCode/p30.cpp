class Solution {
public:
    unordered_map<string, int> wordmap;
    vector<int> cnts, caps, ppos;
    
    void init(const vector<string>& words) {
        for (const string& str : words) {
            auto it = wordmap.find(str);
            if (it != wordmap.end()) {
                caps[it->second]++;
            } else {
                wordmap[str] = caps.size();
                caps.push_back(1);
            }
        }
        cnts.resize(caps.size());
    }

    vector<int> findSubstring(string s, vector<string>& words) {
        if (words.empty()) return {};
        
        init(words);
        ppos.resize(s.size());
        
        int n = (int)s.size(), m = (int)words[0].size();
        for (int i = 0; i < n - m + 1; ++i) {
            auto it = wordmap.find(s.substr(i, m));
            if (it != wordmap.end()) {
                ppos[i] = it->second;
            } else {
                ppos[i] = -1;
            }
        }
        
        vector<int> res;
        
        for (int i = 0; i < m; ++i) {
            fill(cnts.begin(), cnts.end(), 0);
            int l = i, c = 0;
            for (int r = i; r + m - 1 < n; r += m) {
                int pos = ppos[r];
                if (pos != -1) {
                    cnts[pos]++, c++;
                    while (l <= r && cnts[pos] > caps[pos]) {
                        cnts[ppos[l]]--, c--;
                        l += m;
                    }
                    if (c == words.size())
                        res.push_back(l);
                } else {
                    while (l <= r) {
                        if (ppos[l] != -1) cnts[ppos[l]]--, c--;
                        l += m;
                    }
                }
            }
        }
        
        return res;
    }
};
