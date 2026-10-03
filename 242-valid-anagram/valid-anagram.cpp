class Solution {
public:
    bool isAnagram(string s, string t) {
        int n=s.length();
        int m=t.length();
        if(n!=m)return false;
        vector<int> count(26,0);
        for(int i=0;i<n;i++){
            count[s[i]-'a']++;
            count[t[i]-'a']--;
        }
        for(int val:count){
            if(val!=0){
                return false;
            }
        }
        return true;

    
    }
};