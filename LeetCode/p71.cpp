class Solution {
public:
    string simplifyPath(string path) {
        path += '/';
        string res;
        size_t pos, cur = 0;
        while ((pos = path.find('/', cur)) != string::npos) {
            string dir = path.substr(cur, pos - cur);
            if (dir.empty() || dir == ".") {
                // pass
            } else if (dir == "..") {
                size_t res_pos = res.rfind('/');
                if (res_pos != string::npos)
                    res.resize(res_pos);
            } else {
                res += '/';
                res += dir;
            }
            cur = pos + 1;
        }
        return res.empty() ? "/" : res;
    }
};
