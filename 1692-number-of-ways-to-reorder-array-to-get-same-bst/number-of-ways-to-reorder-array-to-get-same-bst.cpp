class Solution {
public:
    int numOfWays(vector<int>& nums) {
        int n = nums.size();
        long long MOD = 1e9 + 7;

        // Pascal's Triangle to precompute combinations (nCr)
        vector<vector<long long>> table(n + 1, vector<long long>(n + 1, 1));
        for (int i = 2; i <= n; i++) {
            for (int j = 1; j < i; j++) {
                table[i][j] = (table[i - 1][j - 1] + table[i - 1][j]) % MOD;
            }
        }

        struct State {
            vector<int> current_nums;
            int status = 0; // 0: initial, 1: left branch pushed, 2: right branch pushed
            long long left_ways = 1;
            long long right_ways = 1;
            vector<int> left;
            vector<int> right;
        };

        vector<State> stack;
        stack.push_back({nums, 0, 1, 1, {}, {}});
        long long last_returned_value = 1;

        while (!stack.empty()) {
            // Must use a reference pointer or index because vector reallocations 
            // inside the loop could invalidate a standard reference (&curr)
            int curr_idx = stack.size() - 1;

            // Base Case: Arrays with 2 or fewer elements only have 1 structural way
            if (stack[curr_idx].current_nums.size() <= 2) {
                last_returned_value = 1;
                stack.pop_back();
                continue;
            }

            if (stack[curr_idx].status == 0) {
                int root = stack[curr_idx].current_nums[0];
                for (size_t i = 1; i < stack[curr_idx].current_nums.size(); i++) {
                    if (stack[curr_idx].current_nums[i] < root) {
                        stack[curr_idx].left.push_back(stack[curr_idx].current_nums[i]);
                    } else {
                        stack[curr_idx].right.push_back(stack[curr_idx].current_nums[i]);
                    }
                }
                stack[curr_idx].status = 1;
                // Push left subtree execution onto the stack
                stack.push_back({stack[curr_idx].left, 0, 1, 1, {}, {}});
            } 
            else if (stack[curr_idx].status == 1) {
                stack[curr_idx].left_ways = last_returned_value;
                stack[curr_idx].status = 2;
                // Push right subtree execution onto the stack
                stack.push_back({stack[curr_idx].right, 0, 1, 1, {}, {}});
            } 
            else if (stack[curr_idx].status == 2) {
                stack[curr_idx].right_ways = last_returned_value;

                // Total ways = (left_ways * right_ways * combinations) % MOD
                long long total_elements = stack[curr_idx].left.size() + stack[curr_idx].right.size();
                long long combinations = table[total_elements][stack[curr_idx].left.size()];
                
                long long subtrees_product = (stack[curr_idx].left_ways * stack[curr_idx].right_ways) % MOD;
                last_returned_value = (subtrees_product * combinations) % MOD;

                stack.pop_back();
            }
        }

        // Subtract 1 from the absolute root total to exclude the original array ordering itself
        return (last_returned_value - 1 + MOD) % MOD;

    }
};