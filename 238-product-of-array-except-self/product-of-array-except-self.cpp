class Solution {
public:
    vector<int> productExceptSelf(vector<int>& nums) {
        int n=nums.size();
        vector<int> res(n,1);
        int left_prod=1;
        int right_prod=1;
        for(int i=0;i<n;i++){
            res[i]*=left_prod;
            left_prod*=nums[i];

            res[n-1-i]*=right_prod;
            right_prod*=nums[n-1-i];
        }
        return res;

    }
};