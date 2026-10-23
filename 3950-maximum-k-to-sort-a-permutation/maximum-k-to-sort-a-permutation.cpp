class Solution {
public:
    int sortPermutation(vector<int>& nums) {
        int n=nums.size();
        int k=-1;
        bool is_sorted=true;
        for(int i=0;i<n-1;i++){
            if(nums[i]!=i){
                is_sorted=false;

                if(k==-1){
                    k=nums[i]&i;
                }
                else{
                    k&=nums[i];
                    k&=i;
                }
            }
        }
        if(is_sorted==true)return 0;
        else return k;
        
    }
};