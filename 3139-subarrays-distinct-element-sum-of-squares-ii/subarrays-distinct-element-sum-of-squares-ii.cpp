class Solution {
    long long MOD = 1e9 + 7;
    vector<long long> sum, sq_sum, lazy;

    void push(int node, int start, int end) {
        if (lazy[node] == 0) return;
        
        int mid = start + (end - start) / 2;
        int left = 2 * node, right = 2 * node + 1;
        long long val = lazy[node];

        // Update left child
        long long lenL = mid - start + 1;
        sq_sum[left] = (sq_sum[left] + 2 * val * sum[left] % MOD + lenL * val % MOD * val % MOD) % MOD;
        sum[left] = (sum[left] + lenL * val) % MOD;
        lazy[left] = (lazy[left] + val) % MOD;

        // Update right child
        long long lenR = end - mid;
        sq_sum[right] = (sq_sum[right] + 2 * val * sum[right] % MOD + lenR * val % MOD * val % MOD) % MOD;
        sum[right] = (sum[right] + lenR * val) % MOD;
        lazy[right] = (lazy[right] + val) % MOD;

        lazy[node] = 0;
    }

    void update(int node, int start, int end, int l, int r, long long val) {
        if (r < start || end < l) return;
        if (l <= start && end <= r) {
            long long len = end - start + 1;
            sq_sum[node] = (sq_sum[node] + 2 * val * sum[node] % MOD + len * val % MOD * val % MOD) % MOD;
            sum[node] = (sum[node] + len * val) % MOD;
            lazy[node] = (lazy[node] + val) % MOD;
            return;
        }
        push(node, start, end);
        int mid = start + (end - start) / 2;
        update(2 * node, start, mid, l, r, val);
        update(2 * node + 1, mid + 1, end, l, r, val);
        sum[node] = (sum[2 * node] + sum[2 * node + 1]) % MOD;
        sq_sum[node] = (sq_sum[2 * node] + sq_sum[2 * node + 1]) % MOD;
    }

public:
    int sumCounts(vector<int>& nums) {
        int n = nums.size();
        sum.assign(4 * n, 0);
        sq_sum.assign(4 * n, 0);
        lazy.assign(4 * n, 0);

        unordered_map<int, int> last_pos;
        long long total_sum = 0;

        for (int j = 0; j < n; ++j) {
            int prev_idx = last_pos.count(nums[j]) ? last_pos[nums[j]] : -1;
            
            // Add 1 to the distinct counts of all subarrays starting from (prev_idx + 1) to j
            update(1, 0, n - 1, prev_idx + 1, j, 1);
            
            // Accumulate the current sum of squares of all subarrays ending at j
            total_sum = (total_sum + sq_sum[1]) % MOD;
            
            last_pos[nums[j]] = j;
        }
        return total_sum;
    }
};