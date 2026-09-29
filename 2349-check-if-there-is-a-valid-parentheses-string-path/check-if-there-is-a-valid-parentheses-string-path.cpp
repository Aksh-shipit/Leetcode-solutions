class Solution {
private:
    private:
    int m, n;
    // 3D memoization table: memo[i][j][k] stores the result for state (i, j, balance)
    // -1 = unvisited, 0 = false, 1 = true
    std::vector<std::vector<std::vector<int>>> memo;

    bool dfs(int i, int j, int balance, const std::vector<std::vector<char>>& grid) {
        // Track balance changes upon entering the cell
        balance += (grid[i][j] == '(') ? 1 : -1;

        // Pruning: if there are more ')' than '(' at any point, it's invalid
        if (balance < 0) return false;

        // Pruning: if balance exceeds the remaining steps to reach the end, 
        // it's impossible to close all open parentheses
        if (balance > (m - 1 - i) + (n - 1 - j)) return false;

        // Base case: reached the bottom-right corner
        if (i == m - 1 && j == n - 1) {
            return balance == 0;
        }

        // Return memoized result if already calculated
        if (memo[i][j][balance] != -1) {
            return memo[i][j][balance];
        }

        bool foundPath = false;
        
        // Move Right
        if (j + 1 < n) {
            foundPath = foundPath || dfs(i, j + 1, balance, grid);
        }
        
        // Move Down
        if (i + 1 < m) {
            foundPath = foundPath || dfs(i + 1, j, balance, grid);
        }

        return memo[i][j][balance] = foundPath;
    }
public:
    bool hasValidPath(vector<vector<char>>& grid) {
        m = grid.size();
        n = grid[0].size();

        // The length of any valid path from (0,0) to (m-1, n-1) is m + n - 1
        // Valid parentheses strings must have an even length
        if ((m + n - 1) % 2 != 0) return false;

        // Cannot start with a close parenthesis or end with an open parenthesis
        if (grid[0][0] == ')' || grid[m - 1][n - 1] == '(') return false;

        // The maximum possible balance is bounded by the path length
        int max_balance = (m + n) / 2;
        memo.assign(m, std::vector<std::vector<int>>(n, std::vector<int>(max_balance + 1, -1)));

        return dfs(0, 0, 0, grid);
    }
};