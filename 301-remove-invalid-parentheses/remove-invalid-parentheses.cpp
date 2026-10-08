class Solution {
bool isValid(const std::string& str) {
        int count = 0;
        for (char ch : str) {
            if (ch == '(') {
                count++;
            } else if (ch == ')') {
                count--;
                if (count < 0) return false; // More closing than opening
            }
        }
        return count == 0;
    }

public:
    vector<string> removeInvalidParentheses(string s) {
        vector<string>result;
        if (s.empty()) return {""};

        std::queue<std::string> q;
        std::unordered_set<std::string> visited;

        q.push(s);
        visited.insert(s);

        bool found = false;

        while (!q.empty()) {
            std::string curr = q.front();
            q.pop();

            // If a valid string is found, we process the remaining items 
            // at the current level, but we do not generate deeper levels.
            if (isValid(curr)) {
                result.push_back(curr);
                found = true;
            }

            if (found) continue;

            // Generate all possible states by removing one parenthesis at a time
            for (int i = 0; i < curr.length(); i++) {
                if (curr[i] != '(' && curr[i] != ')') continue; // Skip letters

                // Create a new string by omitting the character at index i
                std::string nextState = curr.substr(0, i) + curr.substr(i + 1);

                if (visited.find(nextState) == visited.end()) {
                    q.push(nextState);
                    visited.insert(nextState);
                }
            }
        }

        return result;
        
    }
};