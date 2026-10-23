class Solution {
public:
    int maxSubArray(vector<int>& nums) {
        int n=nums.size();
        int sum=0;
        int start=0;
        int ansStart=-1;
        int ansEnd=-1;
        int maxi=INT_MIN;
        for(int i=0;i<n;i++){
            start=i;
            sum=sum+nums[i];
            if(sum>maxi){
                maxi=sum;
                ansStart=start;
                ansEnd=i;
            }
            if(sum<0){
                sum=0;
            }
        }
        return maxi;
    }
};