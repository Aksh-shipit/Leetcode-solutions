class Solution {
public:
    int sumCounts(vector<int>& nums) {
        int total_sum=0;
        int n=nums.size();
        for(int i=0;i<n;i++){
            unordered_set<int> distinct_elements;
            for(int j=i;j<n;j++){
                distinct_elements.insert(nums[j]);
                int distinct_count=distinct_elements.size();
                total_sum+=distinct_count* distinct_count;
            }
        }
        return total_sum;
    }
};