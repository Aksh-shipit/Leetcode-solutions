class Solution {
public:
    vector<int> productExceptSelf(vector<int>& nums) {
        int n=nums.size();
        int totalProduct=1;
        int zerocount=0;
        for(int i=0;i<n;i++){
            if(nums[i]==0)zerocount++;
            else totalProduct*=nums[i];
        }
        vector<int> res(n);
        for(int i=0;i<n;i++){
            if(zerocount==0){
                res[i]=totalProduct/nums[i];
            }
            else if(zerocount==1){
                if(nums[i]==0){
                    res[i]=totalProduct;
                }
                else res[i]=0;
            }
            else{
                res[i]=0;
            }
        }
        return res;
         

    }
};