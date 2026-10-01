class Solution {
private:
    void processConcat(std::vector<std::set<std::string>>& st, std::vector<int>& ops) {
        if (st.size() < 2) return; // Prevent stack underflow
        ops.pop_back();
        std::set<std::string> right = st.back(); st.pop_back();
        std::set<std::string> left = st.back(); st.pop_back();
        
        std::set<std::string> res;
        for (const auto& l : left) {
            for (const auto& r : right) {
                res.insert(l + r);
            }
        }
        st.push_back(res);
    }

    void processUnion(std::vector<std::set<std::string>>& st, std::vector<int>& ops) {
        if (st.size() < 2) return; // Prevent stack underflow
        ops.pop_back();
        std::set<std::string> right = st.back(); st.pop_back();
        std::set<std::string> left = st.back(); st.pop_back();
        
        left.insert(right.begin(), right.end());
        st.push_back(left);
    }

public:
    std::vector<std::string> braceExpansionII(std::string expression) {
        std::vector<std::set<std::string>> st;
        std::vector<int> ops;

        for(int i = 0; i < expression.length(); ++i){
            char c = expression[i];

            if(c == '{'){
                // Fixed: Added parentheses to ensure i > 0 safely protects expression[i-1]
                if(i > 0 && (expression[i-1] == '}' || std::isalpha(expression[i-1]))){
                    ops.push_back(1); // Push implicit concatenation
                }
                ops.push_back(c); // Fixed: Always push the actual '{' marker
            }
            else if(c == ','){
                // Added: Process pending concatenations before pushing a union separator
                while(!ops.empty() && ops.back() == 1){
                    processConcat(st, ops);
                }
                ops.push_back(2); // 2 represents Union (comma)
            }
            else if(c == '}'){
                while(!ops.empty() && ops.back() != '{'){
                    if(ops.back() == 1){
                        processConcat(st, ops);
                    }
                    else if(ops.back() == 2){
                        processUnion(st, ops);
                    }
                }
                if(!ops.empty()) ops.pop_back(); // Pop the '{' marker

                while(!ops.empty() && ops.back() == 1){
                    processConcat(st, ops);
                }
            }
            else if(std::isalpha(c)){
                std::string word = "";
                while(i < expression.length() && std::isalpha(expression[i])){
                    word += expression[i];
                    i++;                
                }
                i--;
                st.push_back({word});

                // Fixed: Explicit parentheses grouping to ensure safe indexing
                if (i - (int)word.length() >= 0 && (expression[i - word.length()] == '}' || std::isalpha(expression[i - word.length()]))) {
                    ops.push_back(1);
                    processConcat(st, ops);
                }
            }
        }
        
        while (!ops.empty()) {
            if (ops.back() == 1) processConcat(st, ops);
            else if (ops.back() == 2) processUnion(st, ops);
            else ops.pop_back();
        }
        
        if (st.empty()) return {};
        std::vector<std::string> result(st.back().begin(), st.back().end());
        return result;
    }
};