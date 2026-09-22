class Solution {
    private:
    struct Node {
        vector<int> cnt; // cnt[x] represents how many prefixes matching x accumulate at this range level
        int total_mul;   // tracks the full range product modulo k
        
        Node(int k) {
            cnt.assign(k, 0);
            total_mul = 1;
        }
    };

    int K;
    vector<Node> tree;

    void merge(Node& parent, const Node& left, const Node& right) {
        parent.total_mul = (left.total_mul * right.total_mul) % K;
        for (int x = 0; x < K; ++x) {
            parent.cnt[x] = left.cnt[x];
        }
        for (int x = 0; x < K; ++x) {
            int target_mod = (x * left.total_mul) % K;
            parent.cnt[target_mod] += right.cnt[x];
        }
    }

    void build(const vector<int>& nums, int node, int start, int end) {
        if (start == end) {
            int val = nums[start] % K;
            tree[node].total_mul = val;
            tree[node].cnt[val] = 1;
            return;
        }
        int mid = start + (end - start) / 2;
        build(nums, 2 * node, start, mid);
        build(nums, 2 * node + 1, mid + 1, end);
        merge(tree[node], tree[2 * node], tree[2 * node + 1]);
    }


    void update(int node, int start, int end, int idx, int val) {
        if (start == end) {
            tree[node].cnt.assign(K, 0);
            int mod_val = val % K;
            tree[node].total_mul = mod_val;
            tree[node].cnt[mod_val] = 1;
            return;
        }
        int mid = start + (end - start) / 2;
        if (idx <= mid) {
            update(2 * node, start, mid, idx, val);
        } else {
            update(2 * node + 1, mid + 1, end, idx, val);
        }
        merge(tree[node], tree[2 * node], tree[2 * node + 1]);
    }

    Node query(int node, int start, int end, int l, int r) {
        if (l <= start && end <= r) {
            return tree[node];
        }
        int mid = start + (end - start) / 2;
        if (r <= mid) {
            return query(2 * node, start, mid, l, r);
        }
        if (l > mid) {
            return query(2 * node + 1, mid + 1, end, l, r);
        }
        Node left_res = query(2 * node, start, mid, l, mid);
        Node right_res = query(2 * node + 1, mid + 1, end, mid + 1, r);
        Node parent_res(K);
        merge(parent_res, left_res, right_res);
        return parent_res;
    }
public:
    vector<int> resultArray(vector<int>& nums, int k, vector<vector<int>>& queries) {
        int n = nums.size();
        K = k;
        tree.assign(4 * n, Node(K));
        
        build(nums, 1, 0, n - 1);
        
        vector<int> result;
        result.reserve(queries.size());
        
        for (const auto& q : queries) {
            int idx = q[0];
            int val = q[1];
            int start = q[2];
            int xi = q[3];
            
            // Perform the point update in O(k log n)
            update(1, 0, n - 1, idx, val);
            
            // Execute the range query from start to the end of the array in O(k log n)
            Node res_node = query(1, 0, n - 1, start, n - 1);
            
            result.push_back(res_node.cnt[xi]);
        }
        
        return result;
        
    }
};