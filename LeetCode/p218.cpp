class Solution {
    struct Line {
        int x, y, type;
        bool operator < (const Line& rhs) const {
            return x < rhs.x;
        }
    };
public:
    vector<vector<int>> getSkyline(vector<vector<int>>& buildings) {
        vector<Line> lines;
        for (auto item : buildings) {
            lines.push_back({item[0], item[2], 0});
            lines.push_back({item[1], item[2], 1});
        }
        sort(lines.begin(), lines.end());
        
        vector<vector<int>> res;
        multiset<int> heights;
        size_t i = 0;
        int lasty = 0;
        while (i < lines.size()) {
            int x = lines[i].x;
            while (i < lines.size() && x == lines[i].x) {
                if (lines[i].type == 0) {
                    heights.insert(lines[i].y);
                } else {
                    heights.erase(heights.find(lines[i].y));
                }
                i++;
            }
            
            int y = !heights.empty() ? *heights.rbegin() : 0;
            if (y != lasty)
                res.push_back({x, lasty = y});
        }
        return res;
    }
};
