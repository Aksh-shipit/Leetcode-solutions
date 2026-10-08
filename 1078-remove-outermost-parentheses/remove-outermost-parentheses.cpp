class Solution {
public:
    string removeOuterParentheses(string s) {
        string ans="";
        int n=s.length();
        int count=0;
        for(char c:s){
            if(c=='('){
                count++;
                if(count>1)ans.push_back(c);
            }
            else{
                count--;
                if(count>0)ans.push_back(c);
            }
        }
        return ans;
    }
};