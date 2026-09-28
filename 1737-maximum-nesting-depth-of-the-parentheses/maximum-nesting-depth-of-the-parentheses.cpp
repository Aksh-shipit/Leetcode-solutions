class Solution {
public:
    int maxDepth(string s) {
        int len=s.length();
        int count=0;
        int maxCount=0;
        for(int i=0;i<len;i++){
            if(s[i]=='('){
                count++;
            }
            else if(s[i]==')'){
                count--;

            }
            else continue;
            maxCount=max(maxCount,count);

        }
        return maxCount;
    }
};