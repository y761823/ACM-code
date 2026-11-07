class Solution {
public:
    constexpr static int kMonthDays[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

    int dayFromOrigin(const string &date) {
        int y, m, d;
        sscanf(date.c_str(), "%d-%d-%d", &y, &m, &d);

        int leap_cnt = y / 4 - y / 100 + y / 400;
        bool is_leap = (y % 4 == 0 && y % 100 != 0) || y % 400 == 0;

        int res = (y - 1) * 365 + (leap_cnt - is_leap);
        for (int i = 0; i < (m - 1); ++i) {
            res += kMonthDays[i];
        }
        if (is_leap && m > 2) res++;
        res += d;
        return res;
    }

    int daysBetweenDates(string date1, string date2) {
        return std::abs(dayFromOrigin(date2) - dayFromOrigin(date1));
    }
};
