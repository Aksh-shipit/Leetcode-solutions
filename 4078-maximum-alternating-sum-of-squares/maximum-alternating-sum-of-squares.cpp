class Solution {
public:
    long long maxAlternatingSum(vector<int>& nums) {
        int n=nums.size();
        vector<long long>squares(n);
        for(int i=0;i<n;i++){
            squares[i]=1L*nums[i]*nums[i];
        }
        sort(squares.begin(),squares.end(),greater<long long>());
        long long max_score=0;
        int left=0;
        int right=n-1;
        for(int i=0;i<n;i++){
            if(i%2==0){
                max_score+=squares[left++];
            }
            else{
                max_score-=squares[right--];
            }
        }
        return max_score;
    }
};