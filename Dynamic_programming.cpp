#include <iostream>
#include <vector>
#include <utility>

class CutRod {
    public:
    int CUT-ROD(std::vector<int> p, int n) {
        if (n == 0) {
            return 0;
        }
        int q = -1;
        for (int i = 1; i <= n; ++i) {
            q = std::max(q, p[i] + CUT-ROD(p, n - i));
        }
        return q;
    }
    //Form top to down to solve the problem with Dynamic programming
    int MEMORIZED-CUT-ROD(std::vector<int> p, int n) {
        std::vector<int> r(n + 1, -1);
        return MEMORIZED-CUT-ROD-AUX(p, n, r);
    }
    int MEMORIZED-CUT-ROD-AUX(std::vector<int> p, int n, int r)
    {
        if (r[n] >= 0) {
            return r[n];
        }
        int q = -1;
        if (n == 0) {
            q = 0;
        } else {
            for (int i = 1; i <= n; ++i) {
                q = std::max(q, p[i] + MEMORIZED-CUT-ROD-AUX(p, n - i, r));
            }
        }
        r[n] = q;
        return q;
    }
    //Form down to top to solve the problem with Dynamic programming
    int BOTTOM-UP-CUT-ROD(std::vector<int> p, int n) {
        std::vector<int> r(n + 1, 0);
        for (int j = 1; j <= n; ++j) {
            int q = -1;
            for (int i = 1; i <= j; ++i) {
                q = std::max(q, p[i] + r[j - i]);
            }
            r[j] = q;
        }
        return r[n];
    }
    std::pair <std::vector<int>, std::vector<int>> EXTENFEF-BOTTOM-UP-CUT-ROD(std::vector<int> p, int n) {
        std::vector<int> r(n + 1, 0);
        std::vector<int> s(n + 1, 0);
        for (int j = 1; j <= n; ++j) {
            int q = -1;
            for (int i = 1; i <= j; ++i) {
                if (q < p[i] + r[j - i]) {
                    q = p[i] + r[j - i];
                    s[j] = i;
                }
            }
            r[j] = q;
        }
        return std::make_pair(r,s);
    }
};