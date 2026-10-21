class Solution {
public:
    int minOperations(string s) {
        int n=s.length();
        bool is_sorted=true;
        for(int i=1;i<n;i++){
            if(s[i-1]>s[i]){
                is_sorted=false;
                break;
            }
        }
        if(is_sorted)return 0;
        if(n<=2)return -1;
        int mn=s[0];
        int mx=s[n-1];
        for(char c:s){
            if(c<mn)mn=c;
            if(c>mx)mx=c;
        }
        if(s[0]==mn || s[n-1]==mx) {
            return 1;
        }
        for(int i=1;i<n-1;i++){
            if(s[i]==mn || s[i]==mx){
                return 2;
            }
        }
        return 3;
    }
};