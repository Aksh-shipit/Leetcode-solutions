class Solution {
public:
    int minSwaps(vector<int>& nums) {
      int n=nums.size();
      vector<pair<int,int>>vec(n);
      for(int i=0;i<n;i++){
        vec[i]={nums[i],i};
      }
      sort(vec.begin(),vec.end(),[](const pair<int,int>& a,const pair<int,int>& b){
        int sumA=0;
        int tempA=a.first;
        while(tempA>0){
            sumA+=tempA%10;
            tempA/=10;
        }
        int sumB=0;
        int tempB=b.first;
        while(tempB>0){
            sumB+=tempB%10;
            tempB/=10;
        }
        if(sumA!=sumB){
            return sumA<sumB;
        }
        return a.first<b.first;
      });
      vector<bool> visited(n,false);
      int totalSwaps=0;
      for(int i=0;i<n;i++){
        if(visited[i] || vec[i].second==i){
            continue;
        }
        int cycleSize=0;
        int j=i;

        while(!visited[j]){
            visited[j]=true;
            j=vec[j].second;
            cycleSize++;
        }
        if(cycleSize>0){
            totalSwaps+=(cycleSize-1);
        }
      }
      return totalSwaps;
    }
};