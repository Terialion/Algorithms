#include <string>
#include <vector>
#include <iostream>

std::pair<std::vector<std::vector<int>>, std::vector<std::vector<char>>> LCS_LENGTH_1(std::string X, std::string Y) {
    int m = X.size();
    int n = Y.size();
    std::vector<std::vector<int>> c(m+1, std::vector<int>(n+1, 0));
    std::vector<std::vector<char>> b(m+1, std::vector<char>(n+1, 0));
    for (int i = 1; i <= m; i++) {
        for (int j = 1; j <= n; j++) {
            if (X[i-1] == Y[j-1]) {
                c[i][j] = c[i-1][j-1] + 1;
                b[i][j] = '\\';
            } else if (c[i-1][j] >= c[i][j-1]) {
                c[i][j] = c[i-1][j];
                b[i][j] = '|';
            } else {
                c[i][j] = c[i][j-1];
                b[i][j] = '-';
            }
        }
    }
    return std::make_pair(c, b);
}

void PRINT_LCS(std::vector<std::vector<char>> b, std::string X, int i, int j) {
    if (i == 0 || j == 0) {
        return;
    }
    if (b[i][j] == '\\') {
        PRINT_LCS(b, X, i-1, j-1);
        std::cout << X[i-1];
    } else if (b[i][j] == '|') {
        PRINT_LCS(b, X, i-1, j);
    } else {
        PRINT_LCS(b, X, i, j-1);
    }
}

int LCS_LENGTH_2(std::string X, std::string Y) {
    int m = X.size();
    int n = Y.size();
    if (m < n) {
        return LCS_LENGTH_2(Y, X);
    }
    std::vector<int> previous(n+1, 0);
    std::vector<int> current(n+1, 0);
    for (int i = 1; i <= m; i++) {
        for (int j = 1; j <= n; j++) {
            if (X[i-1] == Y[j-1]) {
                current[j] = previous[j-1] + 1;
            } else {
                current[j] = std::max(previous[j], current[j-1]);
            }
        }
        std::swap(previous, current);
    }
    return previous[n];
}

int LCS_LENGTH_3(const std::string& X, const std::string& Y) {
    int m = X.size();
    int n = Y.size();
    if (m < n) {
        return LCS_LENGTH_3(Y, X);
    }
    std::vector<int> dp(n+1, 0);
    for (int i = 1; i <= m; i++) {
        int prev = 0;
        for (int j = 1; j <= n; j++) {
            int temp = dp[j];
            if (X[i-1] == Y[j-1]) {
                dp[j] = prev + 1;
            } else {
                dp[j] = std::max(dp[j], dp[j-1]);
            }
            prev = temp;
        }
    }
    return dp[n];
}

int main() {
    std::string X = "ABCBDAB";
    std::string Y = "BDCAB";
    int count = 0;
    auto [c, b] = LCS_LENGTH_1(X, Y);
    PRINT_LCS(b, X, X.size(), Y.size());
    std::cout << std::endl;
    std::cout << LCS_LENGTH_2(X, Y) << std::endl;
    std::cout << LCS_LENGTH_3(X, Y) << std::endl;
    system("pause");
    return 0;
}