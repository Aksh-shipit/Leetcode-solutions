class Solution {
public:
    string evaluate(string s, vector<vector<string>>& knowledge) {
        unordered_map<string, string> mapping;
    for (const auto& pair : knowledge) {
        mapping[pair[0]] = pair[1];
    }
    
    string result = "";
    string current_key = "";
    bool in_bracket = false;
    
    for (char ch : s) {
        if (ch == '(') {
            in_bracket = true;
        } 
        else if (ch == ')') {
            in_bracket = false;
            
            // Logic moved inside the ')' block so lookups only happen at the end of a key
            auto it = mapping.find(current_key);
            if (it != mapping.end()) {
                result += it->second;
            } else {
                result += "?";
            }
            current_key = ""; // Reset for the next bracket pair
        } 
        else {
            // This else block handles regular letters inside or outside brackets
            if (in_bracket) {
                current_key += ch;
            } else {
                result += ch;
            }
        }
    }
    return result;
    }
};